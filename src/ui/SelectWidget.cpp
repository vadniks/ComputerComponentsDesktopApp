
#include "SelectWidget.hpp"

SelectWidget::SelectWidget(QWidget* parent, Component* target) :
    QWidget(parent),
    mState(this, target),
    mBaseLayout(this),
    mComponentList(
        this,
        {},
        [this]() -> QPushButton* {
            auto button = Util::makeIconButton(Consts::BACK_ICON);
            connect(button, &QPushButton::clicked, this, [this](){ emit exitRequested(nullptr); });
            return button;
        }(),
        new QString(Consts::COMPONENT_SELECTION),
        mState.fetchedComponents()
    ),
    mDetails(nullptr)
{
    mBaseLayout.addWidget(&mComponentList);
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this,
            &SelectWidget::requestedDetailsForComponent);
}

void SelectWidget::requestedDetailsForComponent(Component* component) {
    if (mDetails) detailsRequestedExit();

    mDetails = new ComponentDetailsWidget(this, component);
    connect(mDetails, &ComponentDetailsWidget::closeClicked, this, &SelectWidget::detailsRequestedExit);
    connect(mDetails, &ComponentDetailsWidget::doneClicked, this, &SelectWidget::componentSelected);
    mBaseLayout.addWidget(mDetails);
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
    mBaseLayout.removeWidget(mDetails);
    mDetails->disconnect();
    delete mDetails;
    mDetails = nullptr;
}

SelectWidget::~SelectWidget() {
    delete mDetails;
}
