
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "../model/Component.hpp"

using ComponentType = Component::ComponentType;

class ComponentListItemWidget final : public QWidget {
    Q_OBJECT
public:
    ComponentListItemWidget(
        QWidget* parent,
        const QIcon& icon,
        const QString& title,
        unsigned cost,
        ComponentType type
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
