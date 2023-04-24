
#include "SelectWidget.hpp"
#include "../Util.hpp"

SelectWidget::SelectWidget(QWidget* parent, Component* target) :
    QWidget(parent),
    mState(this, target),
    mBaseLayout(this),
    mComponentList(
        this,
        { makeIconButton(Consts::REMOVE_ICON, Button::REMOVE) },
        makeIconButton(Consts::BACK_ICON, Button::BACK),
        std::make_optional(new QString(Consts::COMPONENT_SELECTION)),
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
    if (mDetails) {
        mBaseLayout.removeWidget(mDetails);
        mDetails->disconnect();
        delete mDetails;
    }

    mDetails = new ComponentDetailsWidget(this, component);
    mBaseLayout.addWidget(mDetails);
}

SelectWidget::~SelectWidget() {
    delete mDetails;
}
