
#pragma once

#include <QMainWindow>
#include "../state/AppState.hpp"
#include "MessageDisplayableWidget.hpp"
#include "IWindowShared.hpp"

class MainWindow final : public QMainWindow, public IWindowShared {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow() override;
    [[nodiscard]] Widget currentWidget() const override;
private:
    IS_ALIVE
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
