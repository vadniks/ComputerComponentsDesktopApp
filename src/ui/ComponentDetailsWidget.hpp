
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "../model/Component.hpp"

class ComponentDetailsWidget final : public QWidget {
    Q_OBJECT
public:
    ComponentDetailsWidget(QWidget* parent, Component* component);
private:
    QVBoxLayout mBaseLayout;
    QHBoxLayout mTitleCostLayout;
    QHBoxLayout mImageDescriptionLayout;
    QLabel mTitle;
    QLabel mCost;
    QLabel mImage;
    QLabel mDescription;
};
