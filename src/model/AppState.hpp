
#pragma once

#include <QWidget>
#include <QList>
#include "Component.hpp"
#include "../Consts.hpp"

class AppState final {
public:
    AppState();
    ~AppState();

    QWidget* currentWidget = nullptr;
    QList<Component*> selectedComponents;
};
