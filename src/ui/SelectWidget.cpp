
#include "SelectWidget.hpp"

SelectWidget::SelectWidget(QWidget* parent, Component* target) :
    QWidget(parent),
    mState(THIS_RETURNING_PROXY(cIsAlive = true), target),
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
        cIsAlive
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

SelectWidget::~SelectWidget() {
    cIsAlive = false;
    delete mDetails;
}
