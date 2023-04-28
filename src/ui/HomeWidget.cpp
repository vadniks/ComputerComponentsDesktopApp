
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
    ),
    mState(state)
{
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this, &HomeWidget::cartComponentSelected);
    mBody.addWidget(&mComponentList);

    scheduleButtonChange(&AppState::authorized, &HomeWidget::authorizationConfirmed);
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, Button button) {
    auto pushButton = Util::makeIconButton(icon);
    connect(pushButton, &QPushButton::clicked, this, [this, button]() { iconButtonClicked(button); });
    return pushButton;
}

void HomeWidget::logout() { scheduleButtonChange(&AppState::logout, &HomeWidget::loggedOut); }

void HomeWidget::scheduleButtonChange(QFuture<bool> (AppState::*action)(), void (HomeWidget::*slot)()) {
    auto notifier = new Notifier();
    connect(notifier, &Notifier::notify, this, slot);

    (mState.*action)().then([this, notifier, slot](bool authorized){
        if (authorized) emit notifier->notify(nullptr);

        disconnect(notifier, &Notifier::notify, this, slot);
        delete notifier;
    });
}

void HomeWidget::changeButton(const QString& icon, Button button) {
    auto newButton = makeIconButton(icon, button),
        prevButton = mComponentList.appBar().buttonList()[1];

    mComponentList.appBar().buttons().replaceWidget(prevButton, newButton);

    prevButton->disconnect();
    delete prevButton;

    mComponentList.appBar().buttonList()[1] = newButton;
}

#define CASE(x, y) \
    case Button::x: \
        emit y ## Requested(); \
        break;

void HomeWidget::iconButtonClicked(Button button) { switch (button) {
    CASE(LOGIN, login)
    CASE(INFO, info)
    case Button::LOGOUT: logout(); break;
} }

void HomeWidget::authorizationConfirmed() { changeButton(Consts::LOGOUT_ICON, Button::LOGOUT); }
void HomeWidget::loggedOut() { changeButton(Consts::LOGIN_ICON, Button::LOGIN); }
