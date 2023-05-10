
#pragma once

#include <QMainWindow>
#include "../state/AppState.hpp"
#include "MessageDisplayableWidget.hpp"

class MainWindow final : public QMainWindow {
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
};
