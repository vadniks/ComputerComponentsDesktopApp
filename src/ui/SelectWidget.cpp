
#include "SelectWidget.hpp"

SelectWidget::SelectWidget(QWidget* parent, Component* target) :
    QWidget(parent),
    mState(this, target),
    mBaseLayout(this),
    mComponentList(
        this,
        { makeIconButton(Consts::REMOVE_ICON, Button::REMOVE) },
        makeIconButton(Consts::BACK_ICON, Button::BACK),
        new QString(Consts::COMPONENT_SELECTION),
        mState.fetchedComponents()
    ),
    mDetails(nullptr)
{
    mBaseLayout.addWidget(&mComponentList);
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this, &SelectWidget::componentClicked);
}

QPushButton* SelectWidget::makeIconButton(const QString& icon, Button which) {
    auto button = Util::makeIconButton(icon);
    connect(button, &QPushButton::clicked, this, [this, which](){ iconButtonClicked(which); });
    return button;
}

void SelectWidget::iconButtonClicked(Button button) {
    if (button == Button::BACK)
        emit exitRequested(nullptr);
}

void SelectWidget::componentClicked(Component* component) {
    if (mDetails) detailsRequestedExit();

    mDetails = new ComponentDetailsWidget(this, component);
    mBaseLayout.addWidget(mDetails);
}

void SelectWidget::componentSelected() {

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
