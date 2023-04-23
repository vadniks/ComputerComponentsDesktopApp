
#include <QDebug>
#include <QTimer>
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

    mListWidget.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    connect(&mListWidget, &QListWidget::itemClicked, this, &HomeWidget::listItemClicked);
    fillList();
}

QPushButton* HomeWidget::makeIconButton(const QString& icon, IconButton button) {
    auto pushButton = new QPushButton(QIcon(icon), QString());

    pushButton->setFixedSize(UIConsts::ICON_SIZE, UIConsts::ICON_SIZE);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(UIConsts::ICON_SIZE - 5, UIConsts::ICON_SIZE - 5));

    connect(pushButton, &QPushButton::clicked, this, [this, button](){ iconButtonClicked(button); });
    return pushButton;
}

void HomeWidget::fillList() {
    QListWidgetItem* item;
    QWidget* widget;
    Component* component;

    for (unsigned i = 0; i < Component::COMPONENTS; i++)
        component = new Component( // TODO: test only
            QString(UIConsts::TITLE),
            static_cast<ComponentType>(i),
            QString(),
            i
        ),
        mComponents.push_back(component),

        widget = new ComponentListItemWidget(this, component),

        item = new QListWidgetItem(),
        item->setSizeHint(widget->sizeHint()),

        mListItems.push_back({item, widget}),

        mListWidget.addItem(item),
        mListWidget.setItemWidget(item, widget);
}

void HomeWidget::iconButtonClicked(IconButton button) {
    qDebug() << (button == IconButton::INFO ? "info" : "login"); // TODO: test only
}

void HomeWidget::listItemClicked(QListWidgetItem* item) {
    qDebug() << mListWidget.indexFromItem(item).row(); // TODO
    QTimer::singleShot(100, this, &HomeWidget::listItemDeselectRequested);
}

void HomeWidget::listItemDeselectRequested() { mListWidget.clearSelection(); }

HomeWidget::~HomeWidget() {
    for (auto item : mListItems)
        delete item.first,
        delete item.second;

    for (auto component : mComponents)
        delete component;
}
