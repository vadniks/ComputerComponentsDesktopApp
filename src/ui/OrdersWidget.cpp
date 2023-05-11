
#include "OrdersWidget.hpp"

OrdersWidget::OrdersWidget(QWidget* parent) :
    QWidget(parent),
    mBody(THIS_RETURNING_PROXY(cIsAlive = true)),
    mAppBar(
        this,
        Consts::APP_NAME,
        new QString(Consts::ORDERS),
        {},
        BACK_ICON_BUTTON
    ),
    mTabBase(this),
    mNewOrderTab(this),
    mNewOrderBody(&mNewOrderTab),
    mSubmitOrder(Consts::SUBMIT_ORDER),
    mSubmit(Consts::SUBMIT),
    mHistoryTab(this),
    mHistoryBody(&mHistoryTab),
    mOrders(this, nullptr, mState.boughtComponents(), cIsAlive),
    mClearHistory(Consts::CLEAR)
{
    mBody.addWidget(&mAppBar);
    mBody.addWidget(&mTabBase);

    mTabBase.addTab(&mNewOrderTab, Consts::ORDERS);
    mTabBase.addTab(&mHistoryTab, Consts::HISTORY);
    mTabBase.tabBar()->setDocumentMode(true);

    mNewOrderBody.setAlignment(Qt::AlignCenter);

    mSubmitOrder.setStyleSheet(u8"font-size: 18px");

    auto textColorCss = Util::makePlaceholderTextColorCss(palette());

    mFirstName.setPlaceholderText(Consts::FIRST_NAME);
    mFirstName.setStyleSheet(textColorCss);

    mLastName.setPlaceholderText(Consts::LAST_NAME);
    mLastName.setStyleSheet(textColorCss);

    mPhone.setPlaceholderText(Consts::PHONE_NUMBER);
    mPhone.setStyleSheet(textColorCss);
    mPhone.setValidator(&mPhoneValidator);

    mAddress.setPlaceholderText(Consts::ADDRESS);
    mAddress.setStyleSheet(textColorCss);

    mNewOrderBody.addWidget(&mSubmitOrder, 0, Qt::AlignHCenter);
    mNewOrderBody.addWidget(&mFirstName);
    mNewOrderBody.addWidget(&mLastName);
    mNewOrderBody.addWidget(&mPhone);
    mNewOrderBody.addWidget(&mAddress);
    mNewOrderBody.addWidget(&mSubmit, 0 , Qt::AlignHCenter);

    mHistoryBody.addWidget(&mOrders);
    mHistoryBody.addWidget(&mClearHistory, 0 , Qt::AlignHCenter);
    mHistoryBody.setContentsMargins(0, 0, 0, 0);

    resizeEvent(nullptr);

    connect(&mSubmit, &QPushButton::clicked, this, &OrdersWidget::submitClicked);
    connect(&mClearHistory, &QPushButton::clicked, this, &OrdersWidget::clearClicked);

    fetchOrders();
}

void OrdersWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);
    const auto width = this->width() / 2;

    mFirstName.setMaximumWidth(width);
    mLastName.setMaximumWidth(width);
    mPhone.setMaximumWidth(width);
    mAddress.setMaximumWidth(width);
}

void OrdersWidget::fetchOrders() {
    mState.fetchHistory().then([this]()
    { Util::switchThreads(this, &OrdersWidget::historyFetched, nullptr, cIsAlive); });
}

void OrdersWidget::updateOrdersList() {
    mState.dropBoughtComponents();
    fetchOrders();
}

void OrdersWidget::submitClicked() {
    OrdersState::submitOrder(
        mFirstName.text(),
        mLastName.text(),
        mPhone.text(),
        mAddress.text()
    ).then([this](bool successful) {
        Util::notifySuccessfulOrFailed(successful);
        if (successful) updateOrdersList();
    });
}

void OrdersWidget::clearClicked() {
    OrdersState::clearHistory().then([this](bool successful){
        Util::notifySuccessfulOrFailed(successful);
        if (successful) Util::switchThreads(this, &OrdersWidget::historyCleared, nullptr, cIsAlive);
    });
}

void OrdersWidget::historyCleared() {
    mState.dropBoughtComponents();
    mOrders.reFillList();
}

void OrdersWidget::historyFetched() { mOrders.reFillList(); }
OrdersWidget::~OrdersWidget() { cIsAlive = false; }
