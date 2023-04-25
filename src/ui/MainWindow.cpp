
#include "MainWindow.hpp"
#include "HomeWidget.hpp"
#include "SelectWidget.hpp"

MainWindow::MainWindow() {
    mAppState.setCurrentWidget(new HomeWidget(this, mAppState));
    connectHomeWidget();
    setCentralWidget(mAppState.currentWidget());

    setMinimumSize(Consts::APP_WIDTH, Consts::APP_HEIGHT);
    show();
}

void MainWindow::connectHomeWidget() {
    connect(
        dynamic_cast<HomeWidget*>(mAppState.currentWidget()),
        &HomeWidget::cartComponentSelected,
        this,
        &MainWindow::cartComponentTypeSelected
    );
}

void MainWindow::replaceWidgetWith(QWidget* widget) {
    setCentralWidget(widget);
    mAppState.currentWidget()->disconnect();
    delete mAppState.currentWidget();
    mAppState.setCurrentWidget(widget);
}

void MainWindow::cartComponentTypeSelected(Component* component) {
    auto widget = new SelectWidget(this, component);
    connect(widget, &SelectWidget::exitRequested, this, &MainWindow::exitRequested);
    replaceWidgetWith(widget);
}

void MainWindow::exitRequested([[maybe_unused]] void* parameter) {
    auto widget = new HomeWidget(this, mAppState);
    replaceWidgetWith(widget);
    connectHomeWidget();
}

MainWindow::~MainWindow() { delete mAppState.currentWidget(); }
