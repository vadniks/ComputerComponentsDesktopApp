
#include "AppBarWidget.hpp"

AppBarWidget::AppBarWidget(
    QWidget* parent,
    const QString& title,
    QList<QPushButton*>&& buttons,
    QPushButton* leftButton
) :
    QWidget(parent),
    mBaseLayout(this),
    mTitle(title),
    mButtons(std::move(buttons)),
    mButtonLayout(nullptr),
    mLeftButton(leftButton)
{
    mTitle.setStyleSheet(u8R"(
        font-size: 20px;
        font-style: italic;
        font-weight: bold;
    )");

    if (mLeftButton) mBaseLayout.addWidget(mLeftButton);
    mBaseLayout.addWidget(&mTitle);
    mBaseLayout.addLayout(&mButtonLayout);

    for (auto button : mButtons) mButtonLayout.addWidget(button);
}

AppBarWidget::~AppBarWidget() {
    for (auto button : mButtons) delete button;
    delete mLeftButton;
}
