
#include "MainWindow.hpp"
#include "HomeWidget.hpp"
#include "SelectWidget.hpp"

MainWindow::MainWindow() {
    mAppState.setCurrentWidget(new HomeWidget(this, mAppState));
    connect(
        dynamic_cast<HomeWidget*>(mAppState.currentWidget()),
        &HomeWidget::cartComponentSelected,
        this,
        &MainWindow::cartComponentTypeSelected
    );

    setCentralWidget(mAppState.currentWidget());
    setMinimumSize(Consts::APP_WIDTH, Consts::APP_HEIGHT);
    show();
}

void MainWindow::cartComponentTypeSelected(Component* component) {
    auto widget = new SelectWidget(this, component);
    setCentralWidget(widget);

    mAppState.currentWidget()->disconnect();
    delete mAppState.currentWidget();

    mAppState.setCurrentWidget(widget);
}

MainWindow::~MainWindow() { delete mAppState.currentWidget(); }
