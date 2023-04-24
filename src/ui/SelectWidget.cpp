
#include "SelectWidget.hpp"
#include "../Util.hpp"
#include "../Consts.hpp"

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
    )
{
    mBaseLayout.addWidget(&mComponentList);
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
