
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
    mHistoryTab(this),
    mHistoryBody(&mHistoryTab),
    mOrders(this, nullptr, {}),
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

    mHistoryBody.addWidget(&mOrders);
    mHistoryBody.addWidget(&mClearHistory);

    resizeEvent(nullptr);
}

void OrdersWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);
    const auto width = this->width() / 2;

    mFirstName.setMaximumWidth(width);
    mLastName.setMaximumWidth(width);
    mPhone.setMaximumWidth(width);
    mAddress.setMaximumWidth(width);
}
