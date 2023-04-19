
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include "AppBar.hpp"

class HomeWidget final : public QWidget {
    Q_OBJECT
public:
    explicit HomeWidget(QWidget* parent);
    ~HomeWidget() override;
private:
    enum IconButton { INFO, LOGIN };

    QVBoxLayout mBaseLayout;
    AppBar mAppBar;
    QListView mListView;

    QPushButton* makeIconButton(const QString& icon, IconButton button);

private slots:
    static void iconButtonClicked(HomeWidget::IconButton button);
};
