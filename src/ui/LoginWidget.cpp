
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
    mWelcome(Consts::WELCOME_ANON),
    mProceed(Consts::PROCEED),
    mClear(Consts::CLEAR)
{
    mWelcome.setStyleSheet(u8R"(
        font-style: italic;
        font-size: 16px;
    )");

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

    mBodyProxyLayout.addStretch();
    mBodyProxyLayout.addLayout(&mControlsLayout);
    mBodyProxyLayout.addStretch();

    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addStretch(1);
    mBaseLayout.addWidget(&mImage, 0, Qt::AlignCenter);
    mBaseLayout.addWidget(&mWelcome, 0, Qt::AlignCenter);
    mBaseLayout.addStretch(1);
    mBaseLayout.addLayout(&mBodyProxyLayout);
    mBaseLayout.addStretch(3);

    resizeEvent(nullptr);
}

void LoginWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);

    const auto size = static_cast<int>(static_cast<float>(width()) * 0.25f);
    mImage.setPixmap(QIcon(Consts::PC_ICON).pixmap(size));
}

void LoginWidget::proceedClicked() {

}

void LoginWidget::clearClicked() {

}
