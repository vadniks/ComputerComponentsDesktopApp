
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/SelectState.hpp"

class SelectWidget final : public QWidget {
    Q_OBJECT
public:
    SelectWidget(QWidget* parent, Component* target);
private:
    Component* mTargetComponent;
    SelectState mState;
    QVBoxLayout mBaseLayout;
    BaseComponentListWidget mComponentList;
private slots:
    void iconButtonClicked();
};
