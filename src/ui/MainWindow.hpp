
#pragma once

#include <QMainWindow>
#include "HomeWidget.hpp"

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow() override;
private:
    HomeWidget mHomeWidget;
};
