
#include "LoginWidget.hpp"
#include "../Consts.hpp"
#include "../Util.hpp"
#include "../state/MessageDispatcher.hpp"
#include "../state/LoginState.hpp"

LoginWidget::LoginWidget(QWidget* parent, const IWindowShared* windowShared) :
    QWidget(parent),
    AbsPrimaryWidget(windowShared),
    mBody(this),
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

    auto textColorCss = Util::makePlaceholderTextColorCss(palette());

    mName.setPlaceholderText(Consts::LOGIN);
    mName.setStyleSheet(textColorCss);

    mPassword.setPlaceholderText(Consts::PASSWORD);
    mPassword.setStyleSheet(textColorCss);
    mPassword.setEchoMode(QLineEdit::Password);

    connect(&mProceed, &QPushButton::clicked, this, &LoginWidget::proceedClicked);
    connect(&mClear, &QPushButton::clicked, this, &LoginWidget::clearClicked);

    mButtons.addWidget(&mProceed);
    mButtons.addWidget(&mClear);

    mControls.addWidget(&mName);
    mControls.addWidget(&mPassword);
    mControls.addLayout(&mButtons);

    mBodyProxy.addStretch();
    mBodyProxy.addLayout(&mControls);
    mBodyProxy.addStretch();

    mBody.addWidget(&mAppBar);
    mBody.addStretch(1);
    mBody.addWidget(&mImage, 0, Qt::AlignCenter);
    mBody.addWidget(&mWelcome, 0, Qt::AlignCenter);
    mBody.addStretch(1);
    mBody.addLayout(&mBodyProxy);
    mBody.addStretch(3);

    resizeEvent(nullptr);
}

void LoginWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);

    const auto size = static_cast<int>(static_cast<float>(Util::minOrMax<true>(width(), height())) * 0.25f);
    mImage.setPixmap(QIcon(Consts::PC_ICON).pixmap(size));
}

void LoginWidget::proceedClicked() {
    LoginState::login(mName.text(), mPassword.text()).then([this](bool successful) {
        Util::notifySuccessfulOrFailed(successful);
        if (successful) emit exitRequested(nullptr);
    });
}

void LoginWidget::clearClicked() {
    mName.setText(Consts::EMPTY);
    mPassword.setText(Consts::EMPTY);
}
