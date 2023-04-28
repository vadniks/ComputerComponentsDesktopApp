
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QPair>
#include "AppBarWidget.hpp"
#include "ComponentListItemWidget.hpp"
#include "../state/AppState.hpp"

class BaseComponentListWidget final : public QWidget {
    Q_OBJECT
public:
    BaseComponentListWidget(
        QWidget* parent,
        QList<QPushButton*>&& buttons,
        QPushButton* _Nullable leftButton,
        const QString* _Nullable subtitle,
        const QList<Component*>& components
    );
    ~BaseComponentListWidget() override;
    void reFillList();
    AppBarWidget& appBar();
private:
    QVBoxLayout mBody;
    AppBarWidget mAppBar;
    QListWidget mListWidget;
    QList<QPair<QListWidgetItem*, QWidget*>> mListItems;
    const QList<Component*>& mComponents;

    void clearListItems();
private slots:
    void listItemClicked(QListWidgetItem* item);
signals:
    void componentSelected(Component* component);
};
