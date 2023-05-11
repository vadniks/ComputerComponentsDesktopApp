
#include "BaseComponentListWidget.hpp"
#include "../Util.hpp"

BaseComponentListWidget::BaseComponentListWidget(
    QWidget* parent,
    AppBarWidget* _Nullable appBar,
    const QList<Component*>& components,
    bool& isParentAlive
) :
    QWidget(parent),
    mIsParentAlive(isParentAlive),
    mBody(this),
    mAppBar(appBar),
    mListWidget(this),
    mComponents(components)
{
    if (mAppBar) mBody.addWidget(mAppBar);
    mBody.addWidget(&mListWidget);

    mListWidget.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    connect(&mListWidget, &QListWidget::itemClicked, this, &BaseComponentListWidget::listItemClicked);
    reFillList();
}

void BaseComponentListWidget::reFillList() {
    clearListItems();

    QListWidgetItem* item;
    QWidget* widget;

    for (auto component : mComponents)
        widget = new ComponentListItemWidget(this, component, mIsParentAlive),

        item = new QListWidgetItem(),
        item->setSizeHint(widget->sizeHint()),

        mListItems.push_back({item, widget}),

        mListWidget.addItem(item),
        mListWidget.setItemWidget(item, widget);
}

AppBarWidget* BaseComponentListWidget::appBar() { return mAppBar; }

bool BaseComponentListWidget::fetching() const {
    for (const auto& item : mListItems) // TODO: std::ranges::any_of()
        if (dynamic_cast<const ComponentListItemWidget*>(item.second)->isFetching())
            return true;
    return false;
}

void BaseComponentListWidget::clearListItems() {
    for (auto item : mListItems)
        delete item.first,
        delete item.second;
    mListItems.clear();
}

void BaseComponentListWidget::listItemClicked(QListWidgetItem* item) {
    mListWidget.clearSelection();
    emit componentSelected(mComponents[mListWidget.indexFromItem(item).row()]);
}

BaseComponentListWidget::~BaseComponentListWidget() {
    clearListItems();
    delete mAppBar;
}
