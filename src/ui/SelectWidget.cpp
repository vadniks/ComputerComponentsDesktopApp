
#include "SelectWidget.hpp"
#include "../Util.hpp"

SelectWidget::SelectWidget(QWidget* parent, const IWindowShared* windowShared, Component* target) :
    QWidget(parent),
    AbsPrimaryWidget(windowShared),
    mState(this, target),
    mBody(this),
    mComponentList(
        this,
        new AppBarWidget(
            this,
            Consts::APP_NAME,
            new QString(Consts::COMPONENT_SELECTION),
            {},
            BACK_ICON_BUTTON
        ),
        mState.fetchedComponents(),
        new std::function([windowShared](){ return windowShared->currentWidget() == IWindowShared::SELECT; })
    ),
    mDetails(nullptr)
{
    mBody.addWidget(&mComponentList);
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this, &SelectWidget::requestedDetailsForComponent);
    connect(&mState, &SelectState::componentsFetched, this, &SelectWidget::componentsFetched);
}

void SelectWidget::requestedDetailsForComponent(Component* component) {
    if (mDetails) detailsRequestedExit();

    mDetails = new ComponentDetailsWidget(this, component);
    connect(mDetails, &ComponentDetailsWidget::closeClicked, this, &SelectWidget::detailsRequestedExit);
    connect(mDetails, &ComponentDetailsWidget::doneClicked, this, &SelectWidget::componentSelected);
    mBody.addWidget(mDetails);
}

void SelectWidget::componentSelected(Component* component) {
    if (mComponentList.fetching()) return;

    SelectState::componentSelected(*(component->id));
    emit exitRequested(
        new QPair<const Component*, Component*>(mState.targetComponent(), new Component(
            component->title,
            component->type,
            component->description,
            component->cost,
            component->image,
            component->id
        ))
    );
}

void SelectWidget::detailsRequestedExit() {
    mBody.removeWidget(mDetails);
    mDetails->disconnect();
    delete mDetails;
    mDetails = nullptr;
}

void SelectWidget::componentsFetched() { mComponentList.reFillList(); }

SelectWidget::~SelectWidget() { delete mDetails; }
