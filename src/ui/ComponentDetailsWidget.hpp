
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include "../model/Component.hpp"

class ComponentDetailsWidget final : public QWidget {
    Q_OBJECT
public:
    ComponentDetailsWidget(QWidget* parent, const Component* component);
    ~ComponentDetailsWidget() override;
    const Component* currentComponent();
    void resizeEvent(QResizeEvent* event) override;
private:
    const Component* mCurrentComponent;
    QVBoxLayout mBaseLayout;
    QHBoxLayout mTitleCostLayout;
    QHBoxLayout mImageDescriptionLayout;
    QLabel mTitle;
    QLabel mCost;
    QLabel mImage;
    QScrollArea mScrollArea;
    QLabel mDescription;
    QHBoxLayout mButtonsLayout;
    QPushButton* mDone;
    QPushButton* mClose;
signals:
    void doneClicked();
    void closeClicked();
};
