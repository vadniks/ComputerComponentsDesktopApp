
#pragma once

#include <QWidget>
#include <QList>
#include "../model/Component.hpp"
#include "../Consts.hpp"
#include "../model/Network.hpp"

class AppState final {
public:
    AppState();
    ~AppState();
    [[nodiscard]] const QList<Component*>& selectedComponents() const;
    void replaceSelected(const Component* old, Component* nw);
private:
    QList<Component*> mSelectedComponents;
    Network mNetwork;
};
