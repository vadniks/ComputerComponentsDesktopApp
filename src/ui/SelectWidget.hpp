
#pragma once

#include <QWidget>
#include "../model/Component.hpp"

class SelectWidget final : public QWidget {
    Q_OBJECT
public:
    SelectWidget(QWidget* parent, Component* target);
private:
    Component* mTargetComponent;
};
