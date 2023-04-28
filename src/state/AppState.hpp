
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
    QWidget* currentWidget();
    void setCurrentWidget(QWidget* widget);
    [[nodiscard]] const QList<Component*>& selectedComponents() const;
    void replaceSelected(const Component* old, Component* nw);
private:
    QWidget* mCurrentWidget = nullptr;
    QList<Component*> mSelectedComponents;
    Network mNetwork;
};
