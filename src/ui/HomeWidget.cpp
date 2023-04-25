
#include "HomeWidget.hpp"
#include "../Util.hpp"

HomeWidget::HomeWidget(QWidget* parent, const AppState& state) :
    QWidget(parent),
    mBody(this),
    mComponentList(
        this,
        {
            makeIconButton(Consts::INFO_ICON, Button::INFO),
            makeIconButton(Consts::LOGIN_ICON, Button::LOGIN)
        },
        nullptr,
        nullptr,
        state.selectedComponents()
    )
{
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this, &HomeWidget::cartComponentSelected);
    mBody.addWidget(&mComponentList);
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, Button button) {
    auto pushButton = Util::makeIconButton(icon);
    connect(pushButton, &QPushButton::clicked, this, [this, button]() { iconButtonClicked(button); });
    return pushButton;
}

#define CASE(x, y) \
    case Button::x: \
        emit y ## Requested(); \
        break;

void HomeWidget::iconButtonClicked(Button button) { switch (button) {
    CASE(LOGIN, login)
    CASE(INFO, info)
} }
