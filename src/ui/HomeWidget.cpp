
#include "HomeWidget.hpp"
#include "../Util.hpp"

HomeWidget::HomeWidget(QWidget* parent, const AppState& state) :
    QWidget(parent),
    mBaseLayout(this),
    mComponentList(
        this,
        {
            makeIconButton(Consts::INFO_ICON, Button::INFO),
            makeIconButton(Consts::LOGIN_ICON, Button::LOGIN)
        },
        nullptr,
        std::nullopt,
        state.selectedComponents()
    )
{
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this, &HomeWidget::cartComponentSelected);
    mBaseLayout.addWidget(&mComponentList);
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, Button button) {
    auto pushButton = Util::makeIconButton(icon);
    connect(pushButton, &QPushButton::clicked, this, [this, button]() { iconButtonClicked(button); });
    return pushButton;
}

void HomeWidget::iconButtonClicked(Button button) {

}
