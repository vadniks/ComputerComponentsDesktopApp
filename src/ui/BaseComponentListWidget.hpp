
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
        AppBarWidget* _Nullable appBar,
        const QList<Component*>& components,
        std::function<bool ()>* canDoAsync
    );
    ~BaseComponentListWidget() override;
    void reFillList();
    AppBarWidget* _Nullable appBar();
    [[nodiscard]] bool fetching() const;
private:
    QVBoxLayout mBody;
    AppBarWidget* _Nullable mAppBar;
    QListWidget mListWidget;
    QList<QPair<QListWidgetItem*, QWidget*>> mListItems;
    const QList<Component*>& mComponents;
    std::function<bool ()>* mCanDoAsync;

    void clearListItems();
private slots:
    void listItemClicked(QListWidgetItem* item);
signals:
    void componentSelected(Component* component);
};
