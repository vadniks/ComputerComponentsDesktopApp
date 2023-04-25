
#include <QTimer>
#include "BaseComponentListWidget.hpp"
#include "../Util.hpp"

BaseComponentListWidget::BaseComponentListWidget(
    QWidget* parent,
    QList<QPushButton*>&& buttons,
    QPushButton* leftButton,
    optional<const QString*> subtitle,
    const QList<Component*>& components
) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, Consts::APP_NAME_S, subtitle, std::move(buttons), leftButton),
    mListWidget(this),
    mComponents(components)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListWidget);

    mListWidget.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    connect(&mListWidget, &QListWidget::itemClicked, this, &BaseComponentListWidget::listItemClicked);
    fillList();
}

void BaseComponentListWidget::fillList() {
    QListWidgetItem* item;
    QWidget* widget;

    for (auto component : mComponents)
        widget = new ComponentListItemWidget(this, component),

        item = new QListWidgetItem(),
        item->setSizeHint(widget->sizeHint()),

        mListItems.push_back({item, widget}),

        mListWidget.addItem(item),
        mListWidget.setItemWidget(item, widget);
}

void BaseComponentListWidget::listItemClicked(QListWidgetItem* item) {
    QTimer::singleShot(100, this, [this, item](){
        mListWidget.clearSelection();
        emit componentSelected(mComponents[mListWidget.indexFromItem(item).row()]);
    });
}

BaseComponentListWidget::~BaseComponentListWidget() {
    for (auto item : mListItems)
        delete item.first,
        delete item.second;
}
