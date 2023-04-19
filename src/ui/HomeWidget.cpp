
#include <QDebug>
#include "HomeWidget.hpp"

HomeWidget::HomeWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, u8"Title", {
        makeIconButton(u8":/info.svg", IconButton::INFO),
        makeIconButton(u8":/login.svg", IconButton::LOGIN)
    }),
    mListView(this),
    mItemModel(static_cast<signed>(ITEMS), 1)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListView);

    mListView.setModel(&mItemModel);
    fillList();
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, IconButton button) {
    auto pushButton = new QPushButton(QIcon(icon), QString());

    pushButton->setFixedSize(30, 30);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(25, 25));

    connect(pushButton, &QPushButton::clicked, this, [button](){ iconButtonClicked(button); });
    return pushButton;
}

QStandardItem* HomeWidget::makeListItem(const QIcon& icon, const QString& title, const QString& subtitle, const QString& trailing) {
    auto item = new QStandardItem(); // TODO
    item->setText(title);
    return item;
}

void HomeWidget::fillList() {
    for (unsigned i = 0; i < ITEMS; i++)
        mItemModel.setItem(static_cast<signed>(i), 0, makeListItem(QIcon(), QString::asprintf("%u", i), QString(), QString()));
}

void HomeWidget::iconButtonClicked(IconButton button) {
    qDebug() << (button == IconButton::INFO ? "info" : "login"); // TODO: test only
}

HomeWidget::~HomeWidget() { for (auto item : mListItems) delete item; }
