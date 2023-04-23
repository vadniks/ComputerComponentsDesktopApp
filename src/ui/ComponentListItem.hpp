
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class ComponentListItem final : public QWidget {
    Q_OBJECT
public:
    ComponentListItem(
        QWidget* parent,
        const QIcon& icon,
        const QString& title,
        const QString& description,
        unsigned cost
    );

    [[nodiscard]] QSize sizeHint() const override;
private:
    QHBoxLayout mBaseLayout;
    QVBoxLayout mTitlesLayout;
    QLabel mIcon;
    QLabel mTitle;
    QLabel mDescription;
    QLabel mCost;
};
