
#pragma once

#include <QMainWindow>
#include "../state/AppState.hpp"
#include "MessageDisplayableWidget.hpp"

class IWindowShared {
public:
    enum Widget { HOME, SELECT, ABOUT, LOGIN, ORDERS };
    [[nodiscard]] virtual Widget currentWidget() const = 0; // TODO: supply this dependency to all widgets, each widget should check current widget, if it's not instance of checker's class then it should prevent/abort all async actions as it's been detached & deallocated
};

class MainWindow final : public QMainWindow, public IWindowShared {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow() override;
private:
    AppState mAppState;
    QWidget* mWrappedWidget;
    MessageDisplayableWidget mWidgetWrapper;

    void connectHomeWidget();
    void replaceWidgetWith(QWidget* widget);
private slots:
    void cartComponentTypeSelected(Component* component);
    void exitRequested(void* parameter);
    void loginRequested();
    void infoRequested();
    void selectRequested(Component* component);
    void ordersRequested();
    void ordersRequestedImpl();
};
