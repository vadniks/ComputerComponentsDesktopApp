
#pragma once

#include <QFuture>
#include <QList>
#include "../model/Component.hpp"

class OrdersState final {
public:
    OrdersState();
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
private:
    [[nodiscard]] QFuture<QList<Component*>* _Nullable> fetchHistory();

    QList<Component*> mBoughtComponents;
};
