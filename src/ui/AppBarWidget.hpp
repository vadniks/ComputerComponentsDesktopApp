
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QLabel>

class AppBarWidget final : public QWidget {
    Q_OBJECT
public:
    AppBarWidget(
        QWidget* parent,
        const QString& title,
        QList<QPushButton*>&& buttons,
        QPushButton* leftButton = nullptr
    );
    ~AppBarWidget() override;
private:
    QHBoxLayout mBaseLayout;
    QLabel mTitle;
    QHBoxLayout mButtonLayout;
    QList<QPushButton*> mButtons;
    QPushButton* mLeftButton;
};
