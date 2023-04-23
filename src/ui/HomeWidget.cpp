
#include <QDebug>
#include "HomeWidget.hpp"

HomeWidget::HomeWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, u8"Title", {
        makeIconButton(u8":/info.svg", IconButton::INFO),
        makeIconButton(u8":/login.svg", IconButton::LOGIN)
    }),
    mListWidget(this)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListWidget);

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

void HomeWidget::fillList() {
    QListWidgetItem* item;
    QWidget* widget;

    for (unsigned i = 0; i < ITEMS; i++)
        item = new QListWidgetItem(), // TODO:                              ~~~\/
        widget = new ComponentListItem(this, QIcon(u8":/pc_icon.svg"), u8"Title", u8"", i),
        item->setSizeHint(widget->sizeHint()),
        mListItems.push_back({item, widget}),
        mListWidget.addItem(item),
        mListWidget.setItemWidget(item, widget);
}

void HomeWidget::iconButtonClicked(IconButton button) {
    qDebug() << (button == IconButton::INFO ? "info" : "login"); // TODO: test only
}

HomeWidget::~HomeWidget() {
    for (auto item : mListItems)
        delete item.first,
        delete item.second;
}
