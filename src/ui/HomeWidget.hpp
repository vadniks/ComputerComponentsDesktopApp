
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QPair>
#include "AppBarWidget.hpp"
#include "ComponentListItemWidget.hpp"
#include "../model/AppState.hpp"

class HomeWidget final : public QWidget {
    Q_OBJECT
public:
    HomeWidget(QWidget* parent, AppState& state);
    ~HomeWidget() override;
private:
    enum IconButton { INFO, LOGIN };

    QVBoxLayout mBaseLayout;
    AppBarWidget mAppBar;
    QListWidget mListWidget;
    QList<QPair<QListWidgetItem*, QWidget*>> mListItems;
    AppState& mAppState;

    QPushButton* makeIconButton(const QString& icon, IconButton button);
    void fillList();
private slots:
    void iconButtonClicked(HomeWidget::IconButton button);
    void listItemClicked(QListWidgetItem* item);
signals:
    void cartComponentSelected(Component* component);
};
