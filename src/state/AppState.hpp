
#pragma once

#include <QWidget>
#include <QList>
#include "../model/Component.hpp"
#include "../Consts.hpp"
#include "../model/Network.hpp"
#include "../state/MessageDispatcher.hpp"

class AppState final {
public:
    explicit AppState(MessageDispatcher::MessageDispatcherImpl&& messageDispatcherImpl);
    ~AppState();
    [[nodiscard]] const QList<Component*>& selectedComponents() const;
    void replaceSelected(const Component* old, Component* nw);
private:
    QList<Component*> mSelectedComponents;
    [[maybe_unused]] Network mNetwork; // holds instance
    [[maybe_unused]] MessageDispatcher mMessageDispatcher;
};
