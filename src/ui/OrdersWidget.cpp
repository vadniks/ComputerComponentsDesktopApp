
#include "OrdersWidget.hpp"
#include "../Util.hpp"

OrdersWidget::OrdersWidget(QWidget* parent) :
    QWidget(parent),
    mBody(this),
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
    mFirstName(Consts::FIRST_NAME),
    mLastName(Consts::LAST_NAME),
    mPhone(Consts::PHONE_NUMBER),
    mAddress(Consts::ADDRESS),
    mHistoryTab(this),
    mHistoryBody(&mHistoryTab),
    mOrders(this, nullptr, {}),
    mClearHistory(Consts::CLEAR)
{
    mBody.addWidget(&mAppBar);
    mBody.addWidget(&mTabBase);

    mTabBase.addTab(&mNewOrderTab, Consts::ORDERS);
    mTabBase.addTab(&mHistoryTab, Consts::HISTORY);

    mNewOrderBody.addWidget(&mSubmitOrder);
    mNewOrderBody.addWidget(&mFirstName);
    mNewOrderBody.addWidget(&mLastName);
    mNewOrderBody.addWidget(&mPhone);
    mNewOrderBody.addWidget(&mAddress);

    mHistoryBody.addWidget(&mOrders);
    mHistoryBody.addWidget(&mClearHistory);
}
