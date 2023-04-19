
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QLabel>

class AppBar final : public QWidget {
    Q_OBJECT
public:
    AppBar(QWidget* parent, const QString& title, QList<QPushButton*>&& buttons);
    ~AppBar() override;
private:
    QHBoxLayout mBaseLayout;
    QLabel mTitle;
    QHBoxLayout mButtonLayout;
    QList<QPushButton*> mButtons;
};
