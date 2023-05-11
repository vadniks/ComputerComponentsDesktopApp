
#pragma once

#include <QFuture>
#include <QList>
#include "../model/Component.hpp"

class OrdersState final {
public:
    OrdersState() = default;
    ~OrdersState();

    QFuture<bool> submitOrder(
        const QString& firstName,
        const QString& lastName,
        const QString& phoneNumber,
        const QString& address
    );

    QFuture<bool> clearHistory();
    [[nodiscard]] const QList<Component*>& boughtComponents() const;
    void dropBoughtComponents();
    QFuture<void> fetchHistory();
private:
    QList<Component*> mBoughtComponents;
};
