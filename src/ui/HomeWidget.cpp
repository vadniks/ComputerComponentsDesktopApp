
#include <QDebug>
#include "HomeWidget.hpp"
#include "UIConsts.hpp"

HomeWidget::HomeWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, UIConsts::APP_NAME, {
        makeIconButton(UIConsts::INFO_ICON, IconButton::INFO),
        makeIconButton(UIConsts::LOGIN_ICON, IconButton::LOGIN)
    }),
    mListWidget(this)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListWidget);

    fillList();
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, IconButton button) {
    auto pushButton = new QPushButton(QIcon(icon), QString());

    pushButton->setFixedSize(UIConsts::ICON_SIZE, UIConsts::ICON_SIZE);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(UIConsts::ICON_SIZE - 5, UIConsts::ICON_SIZE - 5));

    connect(pushButton, &QPushButton::clicked, this, [button](){ iconButtonClicked(button); });
    return pushButton;
}

void HomeWidget::fillList() {
    QListWidgetItem* item;
    QWidget* widget;

    for (unsigned i = 0; i < ITEMS; i++) // TODO: test only
        widget = new ComponentListItemWidget(this, QIcon(UIConsts::PC_ICON), u8"Title", u8"Description", i),

        item = new QListWidgetItem(),
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
