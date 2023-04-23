
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QPair>
#include "AppBarWidget.hpp"
#include "ComponentListItemWidget.hpp"

class HomeWidget final : public QWidget {
    Q_OBJECT
public:
    explicit HomeWidget(QWidget* parent);
    ~HomeWidget() override;
private:
    enum IconButton { INFO, LOGIN };

    static const unsigned ITEMS = 9;

    QVBoxLayout mBaseLayout;
    AppBarWidget mAppBar;
    QListWidget mListWidget;
    QList<QPair<QListWidgetItem*, QWidget*>> mListItems;

    QPushButton* makeIconButton(const QString& icon, IconButton button);
    void fillList();
private slots:
    static void iconButtonClicked(HomeWidget::IconButton button);
};
