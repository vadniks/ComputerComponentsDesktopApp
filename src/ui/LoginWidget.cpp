
#include <QDebug>
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
    int r = 0, g = 0, b = 0, a = 0;
    palette().text().color().getRgb(&r, &g, &b, &a);
    auto textColorCss = QString(u8"color: rgba(%1, %2, %3, %4)").arg(r).arg(g).arg(b).arg(a);

    mName.setPlaceholderText(Consts::LOGIN);
    mName.setStyleSheet(textColorCss);

    mPassword.setPlaceholderText(Consts::PASSWORD);
    mPassword.setStyleSheet(textColorCss);

    connect(&mProceed, &QPushButton::clicked, this, &LoginWidget::proceedClicked);
    connect(&mClear, &QPushButton::clicked, this, &LoginWidget::clearClicked);

    mButtonsLayout.addWidget(&mProceed);
    mButtonsLayout.addWidget(&mClear);

    mControlsLayout.addWidget(&mName);
    mControlsLayout.addWidget(&mPassword);
    mControlsLayout.addLayout(&mButtonsLayout);

    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addStretch();
    mBaseLayout.addLayout(&mControlsLayout);
    mBaseLayout.addStretch();
}

void LoginWidget::resizeEvent(QResizeEvent* event) {

    QWidget::resizeEvent(event);
}

void LoginWidget::proceedClicked() {

}

void LoginWidget::clearClicked() {

}
