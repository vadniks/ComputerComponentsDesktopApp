
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "AppBarWidget.hpp"
#include "BaseComponentListWidget.hpp"
#include "../state/PhoneValidator.hpp"

class OrdersWidget final : public QWidget {
    Q_OBJECT
public:
    explicit OrdersWidget(QWidget* parent);
signals:
    void exitRequested(void* parameter);
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
    PhoneValidator mPhoneValidator;
    QLineEdit mAddress;
    QWidget mHistoryTab;
    QVBoxLayout mHistoryBody;
    BaseComponentListWidget mOrders;
    QPushButton mClearHistory;
};
