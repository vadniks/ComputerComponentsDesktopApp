
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QPair>
#include <optional>
#include "AppBarWidget.hpp"
#include "ComponentListItemWidget.hpp"
#include "../state/AppState.hpp"

using std::optional;

class BaseComponentListWidget final : public QWidget {
    Q_OBJECT
public:
    BaseComponentListWidget(
        QWidget* parent,
        QList<QPushButton*>&& buttons,
        QPushButton* leftButton,
        optional<const QString*> subtitle,
        const QList<Component*>& components
    );
    ~BaseComponentListWidget() override;
private:
    QVBoxLayout mBaseLayout;
    AppBarWidget mAppBar;
    QListWidget mListWidget;
    QList<QPair<QListWidgetItem*, QWidget*>> mListItems;
    const QList<Component*>& mComponents;

    void fillList();
private slots:
    void listItemClicked(QListWidgetItem* item);
signals:
    void componentSelected(Component* component);
};
