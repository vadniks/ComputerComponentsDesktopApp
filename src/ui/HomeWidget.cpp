
#include <QDebug>
#include "HomeWidget.hpp"

HomeWidget::HomeWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, u8"Title", {
        makeIconButton(u8":/info.svg", IconButton::INFO),
        makeIconButton(u8":/login.svg", IconButton::LOGIN)
    }),
    mListView(this)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListView);
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, IconButton button) {
    auto pushButton = new QPushButton(QIcon(icon), QString());

    pushButton->setFixedSize(30, 30);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(25, 25));

    connect(pushButton, &QPushButton::clicked, this, [button](){ iconButtonClicked(button); });
    return pushButton;
}

void HomeWidget::iconButtonClicked(IconButton button) {
    qDebug() << (button == IconButton::INFO ? "info" : "login"); // TODO: test only
}

HomeWidget::~HomeWidget() {

}
