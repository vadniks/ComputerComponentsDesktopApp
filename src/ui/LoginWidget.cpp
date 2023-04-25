
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
        BACK_ICON_BUTTON()
    ),
    mProceed(Consts::PROCEED),
    mClear(Consts::CLEAR)
{
    mName.setPlaceholderText(Consts::LOGIN);
    mPassword.setPlaceholderText(Consts::PASSWORD);

    mButtonsLayout.addWidget(&mProceed);
    mButtonsLayout.addWidget(&mClear);

}

void LoginWidget::proceedClicked() {

}

void LoginWidget::clearClicked() {

}
