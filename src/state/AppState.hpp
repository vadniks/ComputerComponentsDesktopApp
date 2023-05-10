
#pragma once

#include <QWidget>
#include <QList>
#include <QFuture>
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
    [[nodiscard]] QFuture<bool> authorized();
    QFuture<bool> logout();
    [[nodiscard]] QFuture<QList<Component* _Nullable>* _Nullable> fetchSelectedComponents();
    void dropSelected();
    [[nodiscard]] static Component* makeStubComponent(unsigned index);
    QFuture<bool> clearSelected();
    void setSelectedComponentsUpdateCallback(std::optional<std::function<void ()>>&& callback);
private:
    QList<Component*> mSelectedComponents;
    [[maybe_unused]] Network mNetwork;
    [[maybe_unused]] MessageDispatcher mMessageDispatcher;
    std::optional<std::function<void ()>> mSelectedComponentsUpdateCallback;
};
