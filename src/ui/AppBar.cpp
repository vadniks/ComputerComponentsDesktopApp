
#include "AppBar.hpp"

[[gnu::used]]
AppBar::AppBar(
    QWidget* parent, const QString& title, QList<QPushButton*>&& buttons
) :
    QWidget(parent),
    mBaseLayout(this),
    mTitle(title),
    mButtons(std::move(buttons)),
    mButtonLayout(nullptr)
{
    mBaseLayout.addWidget(&mTitle);
    mBaseLayout.addLayout(&mButtonLayout);
    for (auto button : mButtons) mButtonLayout.addWidget(button);
}

AppBar::~AppBar() { for (auto button : mButtons) delete button; }
