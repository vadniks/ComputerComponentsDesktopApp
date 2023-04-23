
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QLabel>

class AppBarWidget final : public QWidget {
    Q_OBJECT
public:
    [[gnu::used]] AppBarWidget(QWidget* parent, const QString& title, QList<QPushButton*>&& buttons);
    ~AppBarWidget() override;
private:
    QHBoxLayout mBaseLayout;
    QLabel mTitle;
    QHBoxLayout mButtonLayout;
    QList<QPushButton*> mButtons;
};
