
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "../model/Component.hpp"

class ComponentListItemWidget final : public QWidget {
    Q_OBJECT
public:
    ComponentListItemWidget(QWidget* parent, Component* component);
protected:
    void resizeEvent(QResizeEvent* event) override;
public:
    [[nodiscard]] QSize sizeHint() const override;
private:
    QHBoxLayout mBaseLayout;
    QVBoxLayout mTitlesLayout;
    QLabel mIcon;
    QLabel mTitle;
    QLabel mDescription;
    QLabel mCost;
    const QString mTitleString;
};
