
#include "AppBarWidget.hpp"

AppBarWidget::AppBarWidget(
    QWidget* parent,
    const QString& title,
    const QString* _Nullable subtitle,
    QList<QPushButton*>&& buttons,
    QPushButton* _Nullable leftButton
) :
    QWidget(parent),
    mBody(this),
    mTitles(nullptr),
    mTitle(title),
    mSubtitle(subtitle ? new QLabel([subtitle]() -> QString {
        auto _subtitle = *subtitle;
        delete subtitle;
        return _subtitle;
    }()) : nullptr),
    mButtons(nullptr),
    mButtonList(std::move(buttons)),
    mLeftButton(leftButton)
{
    mTitle.setStyleSheet(u8R"(
        font-size: 20px;
        font-style: italic;
        font-weight: bold;
    )");

    mTitles.addWidget(&mTitle);
    if (mSubtitle) mTitles.addWidget(mSubtitle);

    if (mLeftButton) mBody.addWidget(mLeftButton);
    mBody.addLayout(&mTitles);
    mBody.addLayout(&mButtons);

    for (auto button : mButtonList) mButtons.addWidget(button);

    setMaximumHeight(mTitles.sizeHint().height() + 10);
}

// TODO: resizeEvent for subtitle

AppBarWidget::~AppBarWidget() {
    delete mSubtitle;
    for (auto button : mButtonList) delete button;
    delete mLeftButton;
}
