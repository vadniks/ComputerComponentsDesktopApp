
#pragma once

#include <QMainWindow>
#include "../state/AppState.hpp"

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow() override;
private:
    AppState mAppState;

    void connectHomeWidget();
    void replaceWidgetWith(QWidget* widget);

    void test(QList<Component*>* a); // TODO: test only

private slots:
    void cartComponentTypeSelected(Component* component);
    void exitRequested(void* parameter);
    void loginRequested();
    void infoRequested();
};
