
#include <QtConcurrent/QtConcurrent>
#include "OrdersState.hpp"

OrdersState::OrdersState() {

}

QFuture<bool> OrdersState::submitOrder(
    const QString& firstName,
    const QString& lastName,
    const QString& phoneNumber,
    const QString& address
) {
    return QtConcurrent::run([](){ return false; });
}

QFuture<bool> OrdersState::clearHistory() {
    return QtConcurrent::run([](){ return false; });
}

QFuture<QList<Component*>* _Nullable> OrdersState::fetchHistory() {
    return QtConcurrent::run([](){ return new QList<Component*>(); });
}

OrdersState::~OrdersState() { for (auto component : mBoughtComponents) delete component; }
