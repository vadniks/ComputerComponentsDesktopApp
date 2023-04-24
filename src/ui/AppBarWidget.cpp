
#include "AppBarWidget.hpp"

AppBarWidget::AppBarWidget(
    QWidget* parent, const QString& title, QList<QPushButton*>&& buttons
) :
    QWidget(parent),
    mBaseLayout(this),
    mTitle(title),
    mButtons(std::move(buttons)),
    mButtonLayout(nullptr)
{
    mTitle.setStyleSheet(u8R"(
        font-size: 20px;
        font-style: italic;
        font-weight: bold;
    )");
    mBaseLayout.addWidget(&mTitle);
    mBaseLayout.addLayout(&mButtonLayout);
    for (auto button : mButtons) mButtonLayout.addWidget(button);
}

AppBarWidget::~AppBarWidget() { for (auto button : mButtons) delete button; }
