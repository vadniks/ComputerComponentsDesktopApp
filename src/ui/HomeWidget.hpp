
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/AppState.hpp"
#include "../Util.hpp"

class HomeWidget final : public QWidget {
    Q_OBJECT

    enum Button : unsigned { INFO = 0, LOGIN = 1, LOGOUT = 2 };
public:
    HomeWidget(QWidget* parent, AppState& state, bool afterLoggingIn);
    ~HomeWidget() override;
    void onSelectedComponentsUpdated();
private:
    [[nodiscard]] QPushButton* makeIconButton(const QString& icon, Button button);
    void logout();
    void scheduleButtonChange(QFuture<bool> (AppState::*action)(), void (HomeWidget::*slot)());
    void changeButton(const QString& icon, Button button);
    void fetchSelectedComponents();
    [[nodiscard]] QString makeTotalCost() const;
private slots:
    void iconButtonClicked(HomeWidget::Button button);
    void authorizationConfirmed();
    void loggedOut();
    void selectedComponentsFetched(QList<Component* _Nullable>* selected);
    void clearSelectedClicked();
    void listItemClicked(Component* component);
signals:
    void cartComponentSelected(Component* component);
    void loginRequested();
    void infoRequested();
    void ordersRequested();
private:
    IS_ALIVE
    QVBoxLayout mBody;
    BaseComponentListWidget mComponentList;
    AppState& mState;
    QHBoxLayout mBottomBar;
    QPushButton mOrders;
    unsigned mCost;
    QLabel mTotal;
    QPushButton mClear;
    volatile bool mFetching = false;
};
