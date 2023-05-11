
#include "HomeWidget.hpp"
#include "../Util.hpp"

HomeWidget::HomeWidget(QWidget* parent, AppState& state, bool afterLoggingIn) :
    QWidget(parent),
    mBody(this),
    mComponentList(
        this,
        new AppBarWidget(
            this,
            Consts::APP_NAME,
            nullptr,
            {
                makeIconButton(Consts::INFO_ICON, Button::INFO),
                makeIconButton(Consts::LOGIN_ICON, Button::LOGIN)
            },
            nullptr
        ),
        state.selectedComponents()
    ),
    mState(state),
    mBottomBar(nullptr),
    mOrders(Consts::ORDERS),
    mCost(0),
    mTotal(makeTotalCost()),
    mClear(Consts::CLEAR)
{
    connect(&mComponentList, &BaseComponentListWidget::componentSelected, this, &HomeWidget::listItemClicked);
    mBody.addWidget(&mComponentList);

    connect(&mClear, &QPushButton::clicked, this, &HomeWidget::clearSelectedClicked);
    connect(&mOrders, &QPushButton::clicked, this, &HomeWidget::ordersRequested);

    const auto margins = mBody.contentsMargins();
    mBottomBar.setContentsMargins(margins.left(), 0, margins.right(), 0);

    mBottomBar.addWidget(&mOrders);
    mBottomBar.addStretch();
    mBottomBar.addWidget(&mTotal);
    mBottomBar.addWidget(&mClear);
    mBody.addLayout(&mBottomBar);

    scheduleButtonChange(&AppState::authorized, &HomeWidget::authorizationConfirmed);
    if (afterLoggingIn) fetchSelectedComponents();
}

void HomeWidget::onSelectedComponentsUpdated() {
    mCost = 0;
    for (auto component : mState.selectedComponents())
        mCost += component->cost;
    mTotal.setText(makeTotalCost());
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, Button button) {
    auto pushButton = Util::makeIconButton(icon);
    connect(pushButton, &QPushButton::clicked, this, [this, button]() { iconButtonClicked(button); });
    return pushButton;
}

void HomeWidget::logout() { scheduleButtonChange(&AppState::logout, &HomeWidget::loggedOut); }

void HomeWidget::scheduleButtonChange(QFuture<bool> (AppState::*action)(), void (HomeWidget::*slot)()) {
    (mState.*action)().then([this, slot](bool authorized)
    { if (authorized) Util::switchThreads(this, slot, nullptr); });
}

void HomeWidget::changeButton(const QString& icon, Button button) {
    auto newButton = makeIconButton(icon, button),
        prevButton = mComponentList.appBar()->buttonList()[1];

    mComponentList.appBar()->buttons().replaceWidget(prevButton, newButton);

    prevButton->disconnect();
    delete prevButton;

    mComponentList.appBar()->buttonList()[1] = newButton;
}

void HomeWidget::fetchSelectedComponents() {
    mFetching = true;
    mState.fetchSelectedComponents().then([this](QList<Component* _Nullable>* _Nullable selected) {
        if (selected) Util::switchThreads(
            this,
            reinterpret_cast<void (HomeWidget::*)(void*)>(&HomeWidget::selectedComponentsFetched),
            selected
        );
        mFetching = false;
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
    for (unsigned i = 0; i < Component::COMPONENTS; i++) {
        auto component = selected->operator[](i);
        if (!component) continue;

        mState.replaceSelected(mState.selectedComponents()[i], component);
    }

    delete selected;
    mComponentList.reFillList();

    onSelectedComponentsUpdated();
}

void HomeWidget::clearSelectedClicked() {
    mState.clearSelected();

    mState.dropSelected();
    mComponentList.reFillList();

    mCost = 0;
    mTotal.setText(makeTotalCost());
}

void HomeWidget::listItemClicked(Component* component)
{ if (!mFetching) emit cartComponentSelected(component); }
