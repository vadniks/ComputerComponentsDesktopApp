
#include <QTimer>
#include "HomeWidget.hpp"

HomeWidget::HomeWidget(QWidget* parent, AppState& state) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, Consts::APP_NAME, {
        makeIconButton(Consts::INFO_ICON, IconButton::INFO),
        makeIconButton(Consts::LOGIN_ICON, IconButton::LOGIN)
    }),
    mListWidget(this),
    mAppState(state)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListWidget);

    mListWidget.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    connect(&mListWidget, &QListWidget::itemClicked, this, &HomeWidget::listItemClicked);
    fillList();
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, IconButton button) {
    auto pushButton = new QPushButton(QIcon(icon), QString());

    pushButton->setFixedSize(Consts::ICON_SIZE, Consts::ICON_SIZE);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(Consts::ICON_SIZE - 5, Consts::ICON_SIZE - 5));

    connect(pushButton, &QPushButton::clicked, this, [this, button](){ iconButtonClicked(button); });
    return pushButton;
}

void HomeWidget::fillList() {
    QListWidgetItem* item;
    QWidget* widget;

    for (auto component : mAppState.selectedComponents)
        widget = new ComponentListItemWidget(this, component),

        item = new QListWidgetItem(),
        item->setSizeHint(widget->sizeHint()),

        mListItems.push_back({item, widget}),

        mListWidget.addItem(item),
        mListWidget.setItemWidget(item, widget);
}

void HomeWidget::iconButtonClicked(IconButton button) {

}

void HomeWidget::listItemClicked(QListWidgetItem* item) {
    QTimer::singleShot(100, this, [this, item](){
        mListWidget.clearSelection();
        emit cartComponentSelected(mAppState.selectedComponents[mListWidget.indexFromItem(item).row()]);
    });
}

HomeWidget::~HomeWidget() {
    for (auto item : mListItems)
        delete item.first,
        delete item.second;
}
