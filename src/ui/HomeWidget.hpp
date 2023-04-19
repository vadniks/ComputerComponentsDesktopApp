
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
    QVBoxLayout mBaseLayout;
    AppBar mAppBar;
    QListView mListView;

    QPushButton* e();

private slots:
    void f();
};
