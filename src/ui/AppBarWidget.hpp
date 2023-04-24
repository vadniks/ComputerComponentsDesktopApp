
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QLabel>
#include <optional>

using std::optional;

class AppBarWidget final : public QWidget {
    Q_OBJECT
public:
    AppBarWidget(
        QWidget* parent,
        const QString& title,
        optional<const QString*> subtitle,
        QList<QPushButton*>&& buttons,
        QPushButton* leftButton = nullptr
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
