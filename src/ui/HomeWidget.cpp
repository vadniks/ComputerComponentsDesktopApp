
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
    mState(state),
    mBottomBar(nullptr),
    mCost(0),
    mTotal(makeTotalCost()),
    mClear(Consts::CLEAR)
{
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this, &HomeWidget::cartComponentSelected);
    mBody.addWidget(&mComponentList);

    connect(&mClear, &QPushButton::clicked, this, &HomeWidget::clearSelectedClicked);

    mBottomBar.addWidget(&mTotal);
    mBottomBar.addWidget(&mClear);
    mBottomBar.setAlignment(Qt::AlignTrailing);
    mBody.addLayout(&mBottomBar);

    scheduleButtonChange(&AppState::authorized, &HomeWidget::authorizationConfirmed);
    fetchSelectedComponents();
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

void HomeWidget::fetchSelectedComponents() {
    auto notifier = new Notifier();

    auto slot = reinterpret_cast<void (HomeWidget::*)(void*)>(&HomeWidget::selectedComponentsFetched);
    connect(notifier, &Notifier::notify, this, slot);

    mState.fetchSelectedComponents().then([notifier, this, slot](QList<Component* _Nullable>* _Nullable selected){
        if (selected) emit notifier->notify(selected);
        disconnect(notifier, &Notifier::notify, this, slot);
        delete notifier;
    });
}

QString HomeWidget::makeTotalCost() const { return QString(Consts::TOTAL_COST) + QString(u8": %1").arg(mCost); }

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

void HomeWidget::selectedComponentsFetched(QList<Component* _Nullable>* selected) {
    mCost = 0;

    for (unsigned i = 0; i < Component::COMPONENTS; i++) {
        auto component = selected->operator[](i);
        if (!component) continue;

        mState.replaceSelected(mState.selectedComponents()[i], component);
        mCost += component->cost;
    }

    delete selected;
    mComponentList.reFillList();

    mTotal.setText(makeTotalCost());
}

void HomeWidget::clearSelectedClicked() {
    mState.dropSelected();
    mComponentList.reFillList();
    mCost = 0;
    mTotal.setText(makeTotalCost());
    // TODO: post clear selected to server
}
