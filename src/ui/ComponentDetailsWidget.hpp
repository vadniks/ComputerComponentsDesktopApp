
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../model/Component.hpp"

class ComponentDetailsWidget final : public QWidget {
    Q_OBJECT
public:
    ComponentDetailsWidget(QWidget* parent, const Component* component);
    ~ComponentDetailsWidget() override;
    const Component* currentComponent();
private:
    const Component* mCurrentComponent;
    QVBoxLayout mBaseLayout;
    QHBoxLayout mTitleCostLayout;
    QHBoxLayout mButtonsLayout;
    QVBoxLayout mTitleCostButtonsLayout;
    QHBoxLayout mImageDescriptionLayout;
    QPushButton* mDone;
    QPushButton* mClose;
    QLabel mTitle;
    QLabel mCost;
    QLabel mImage;
    QLabel mDescription;
signals:
    void doneClicked();
    void closeClicked();
};
