
#pragma once

#include <QWidget>
#include <QVBoxLayout>
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
        const QString* _Nullable subtitle,
        QList<QPushButton*>&& buttons,
        QPushButton* _Nullable leftButton
    );
    ~AppBarWidget() override;
private:
    QHBoxLayout mBaseLayout;
    QVBoxLayout mTitlesLayout;
    QLabel mTitle;
    QLabel* mSubtitle;
    QHBoxLayout mButtonLayout;
    QList<QPushButton*> mButtons;
    QPushButton* mLeftButton;
};
