
#include "LoginWidget.hpp"
#include "../Consts.hpp"
#include "../Util.hpp"

LoginWidget::LoginWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(
        this,
        Consts::APP_NAME,
        new QString(Consts::LOGING_IN),
        {},
        BACK_ICON_BUTTON
    ),
    mProceed(Consts::PROCEED),
    mClear(Consts::CLEAR)
{
    mName.setPlaceholderText(Consts::LOGIN);
    mPassword.setPlaceholderText(Consts::PASSWORD);

    connect(&mProceed, &QPushButton::clicked, this, &LoginWidget::proceedClicked);
    connect(&mClear, &QPushButton::clicked, this, &LoginWidget::clearClicked);

    mButtonsLayout.addWidget(&mProceed);
    mButtonsLayout.addWidget(&mClear);

    mBaseLayout.addWidget(&mName);
    mBaseLayout.addWidget(&mPassword);
    mBaseLayout.addLayout(&mButtonsLayout);
}

void LoginWidget::proceedClicked() {

}

void LoginWidget::clearClicked() {

}
