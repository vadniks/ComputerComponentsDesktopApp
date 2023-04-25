
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
    QHBoxLayout mBody;
    QVBoxLayout mTitles;
    QLabel mTitle;
    QLabel* mSubtitle;
    QHBoxLayout mButtons;
    QList<QPushButton*> mButtonList;
    QPushButton* mLeftButton;
};
