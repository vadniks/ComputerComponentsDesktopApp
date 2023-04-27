
#include "SelectWidget.hpp"
#include "../Util.hpp"

SelectWidget::SelectWidget(QWidget* parent, Component* target, Network& network) :
    QWidget(parent),
    mState(this, target, network),
    mBody(this),
    mComponentList(
        this,
        {},
        BACK_ICON_BUTTON,
        new QString(Consts::COMPONENT_SELECTION),
        mState.fetchedComponents()
    ),
    mDetails(nullptr)
{
    mBody.addWidget(&mComponentList);
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this,
            &SelectWidget::requestedDetailsForComponent);
}

void SelectWidget::requestedDetailsForComponent(Component* component) {
    if (mDetails) detailsRequestedExit();

    mDetails = new ComponentDetailsWidget(this, component);
    connect(mDetails, &ComponentDetailsWidget::closeClicked, this, &SelectWidget::detailsRequestedExit);
    connect(mDetails, &ComponentDetailsWidget::doneClicked, this, &SelectWidget::componentSelected);
    mBody.addWidget(mDetails);
}

void SelectWidget::componentSelected(Component* component) {
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

SelectWidget::~SelectWidget() {
    delete mDetails;
}
