
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/AppState.hpp"

class HomeWidget final : public QWidget {
    Q_OBJECT

    enum Button : unsigned { INFO = 0, LOGIN = 1, LOGOUT = 2 };
public:
    HomeWidget(QWidget* parent, AppState& state);
private:
    QPushButton* makeIconButton(const QString& icon, Button button);
    void logout();
    void scheduleButtonChange(void (HomeWidget::*slot)());
    void changeButton(const QString& icon, Button button);
private slots:
    void iconButtonClicked(HomeWidget::Button button);
    void authorizationConfirmed();
    void loggedOut();
signals:
    void cartComponentSelected(Component* component);
    void loginRequested();
    void infoRequested();
private:
    QVBoxLayout mBody;
    BaseComponentListWidget mComponentList;
    AppState& mState;
};
