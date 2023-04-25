
#include "AppBarWidget.hpp"

AppBarWidget::AppBarWidget(
    QWidget* parent,
    const QString& title,
    const QString* _Nullable subtitle,
    QList<QPushButton*>&& buttons,
    QPushButton* _Nullable leftButton
) :
    QWidget(parent),
    mBaseLayout(this),
    mTitlesLayout(nullptr),
    mTitle(title),
    mSubtitle(subtitle ? new QLabel([subtitle]() -> QString {
        auto _subtitle = *subtitle;
        delete subtitle;
        return _subtitle;
    }()) : nullptr),
    mButtons(std::move(buttons)),
    mButtonLayout(nullptr),
    mLeftButton(leftButton)
{
    mTitle.setStyleSheet(u8R"(
        font-size: 20px;
        font-style: italic;
        font-weight: bold;
    )");

    mTitlesLayout.addWidget(&mTitle);
    if (mSubtitle) mTitlesLayout.addWidget(mSubtitle);

    if (mLeftButton) mBaseLayout.addWidget(mLeftButton);
    mBaseLayout.addLayout(&mTitlesLayout);
    mBaseLayout.addLayout(&mButtonLayout);

    for (auto button : mButtons) mButtonLayout.addWidget(button);
}

AppBarWidget::~AppBarWidget() {
    delete mSubtitle;
    for (auto button : mButtons) delete button;
    delete mLeftButton;
}
