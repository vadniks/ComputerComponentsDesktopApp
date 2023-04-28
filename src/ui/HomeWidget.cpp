
#include "HomeWidget.hpp"
#include "../Util.hpp"
#include "../Notifier.hpp"

HomeWidget::HomeWidget(QWidget* parent, AppState& state) :
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

    auto notifier = new Notifier();
    connect(notifier, &Notifier::notify, this, &HomeWidget::authorizationConfirmed);
    state.authorized().then([this, notifier](bool authorized){
        if (authorized) emit notifier->notify(nullptr);
        disconnect(notifier, &Notifier::notify, this, &HomeWidget::authorizationConfirmed);
        delete notifier;
    });
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
//    CASE(LOGOUT, logout) // TODO
} }

void HomeWidget::authorizationConfirmed() {
    auto newButton = makeIconButton(Consts::LOGOUT_ICON, Button::LOGOUT),
        prevButton = mComponentList.appBar().buttonList()[1];

    mComponentList.appBar().buttons().replaceWidget(prevButton, newButton);
    delete prevButton;
    mComponentList.appBar().buttonList()[1] = newButton;
}
