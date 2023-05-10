
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
#include "../state/OrdersState.hpp"

class OrdersWidget final : public QWidget {
    Q_OBJECT
public:
    explicit OrdersWidget(QWidget* parent);
signals:
    void exitRequested(void* parameter);
protected:
    void resizeEvent(QResizeEvent* event) override;
private slots:
    void submitClicked();
    void clearClicked();
    void historyCleared();
private:
    OrdersState mState;
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
    QPushButton mSubmit;
    QWidget mHistoryTab;
    QVBoxLayout mHistoryBody;
    BaseComponentListWidget mOrders;
    QPushButton mClearHistory;
};
