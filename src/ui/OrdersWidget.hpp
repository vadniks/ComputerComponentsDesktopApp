
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "AppBarWidget.hpp"
#include "BaseComponentListWidget.hpp"

class OrdersWidget final : public QWidget {
    Q_OBJECT
public:
    OrdersWidget();
private:
    QVBoxLayout mBody;
    AppBarWidget mAppBar;
    QTabWidget mTabBase;
    QWidget mNewOrderTab;
    QVBoxLayout mNewOrderBody;
    QLabel mSubmitOrder;
    QLineEdit mFirstName;
    QLineEdit mLastName;
    QLineEdit mPhone;
    QLineEdit mAddress;
    QWidget mHistoryTab;
    QVBoxLayout mHistoryBody;
    BaseComponentListWidget mOrders;
    QPushButton mClearHistory;
};
