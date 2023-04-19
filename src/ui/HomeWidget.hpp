
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>
#include "AppBar.hpp"

class HomeWidget final : public QWidget {
    Q_OBJECT
public:
    explicit HomeWidget(QWidget* parent);
    ~HomeWidget() override;
private:
    enum IconButton { INFO, LOGIN };

    static const unsigned ITEMS = 10;

    QVBoxLayout mBaseLayout;
    AppBar mAppBar;
    QListView mListView;
    QList<QWidget*> mListItems;
    QStandardItemModel mItemModel;

    QPushButton* makeIconButton(const QString& icon, IconButton button);
    QStandardItem* makeListItem(const QIcon& icon, const QString& title, const QString& subtitle, const QString& trailing);
    void fillList();
private slots:
    static void iconButtonClicked(HomeWidget::IconButton button);
};
