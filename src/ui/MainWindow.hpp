
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
private slots:
    void cartComponentTypeSelected(Component* component);
};
