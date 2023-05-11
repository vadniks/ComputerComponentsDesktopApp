
#include <QtConcurrent/QtConcurrent>
#include "OrdersState.hpp"
#include "../model/Network.hpp"

QFuture<bool> OrdersState::submitOrder(
    const QString& firstName,
    const QString& lastName,
    const QString& phoneNumber,
    const QString& address
) { return QtConcurrent::run([&](){
    return Network::instance()->submitOrder(firstName, lastName, phoneNumber, address); });
}

QFuture<bool> OrdersState::clearHistory() { return QtConcurrent::run([](){ return Network::instance()->clearHistory(); }); }
const QList<Component*>& OrdersState::boughtComponents() const { return mBoughtComponents; }

void OrdersState::dropBoughtComponents() {
    for (auto component : mBoughtComponents) delete component;
    mBoughtComponents.clear();
}

QFuture<void> OrdersState::fetchHistory() {
    return QtConcurrent
        ::run([]() -> QList<Component*>* _Nullable { return Network::instance()->history(); })
        .then([this](QList<Component*>* _Nullable components) {
            if (!components) return;

            for (auto component : *components)
                mBoughtComponents.push_back(component);
            delete components;
        });
}

OrdersState::~OrdersState() { dropBoughtComponents(); }
