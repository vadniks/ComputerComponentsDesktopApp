
#include "MainWindow.hpp"
#include "HomeWidget.hpp"
#include "SelectWidget.hpp"
#include "LoginWidget.hpp"
#include "AboutWidget.hpp"

MainWindow::MainWindow() {
    mAppState.setCurrentWidget(new HomeWidget(this, mAppState));
    connectHomeWidget();
    setCentralWidget(mAppState.currentWidget());

    setMinimumSize(Consts::APP_WIDTH, Consts::APP_HEIGHT);
    show();
}

void MainWindow::connectHomeWidget() {
    auto widget = dynamic_cast<HomeWidget*>(mAppState.currentWidget());
    connect(widget, &HomeWidget::cartComponentSelected, this, &MainWindow::cartComponentTypeSelected);
    connect(widget, &HomeWidget::loginRequested, this, &MainWindow::loginRequested);
    connect(widget, &HomeWidget::infoRequested, this, &MainWindow::infoRequested);
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

void MainWindow::exitRequested(void* parameter) {
    if (parameter != nullptr) {
        auto result = static_cast<QPair<const Component*, Component*>*>(parameter);
        mAppState.replaceSelected(result->first, result->second);
        delete result;
    }

    auto widget = new HomeWidget(this, mAppState);
    replaceWidgetWith(widget);
    connectHomeWidget();
}

void MainWindow::loginRequested() {
    auto widget = new LoginWidget(this);
    connect(widget, &LoginWidget::exitRequested, this, &MainWindow::exitRequested);
    replaceWidgetWith(widget);
}

void MainWindow::infoRequested() {
    auto widget = new AboutWidget(this);
    connect(widget, &AboutWidget::exitRequested, this, &MainWindow::exitRequested);
    replaceWidgetWith(widget);
}

MainWindow::~MainWindow() { delete mAppState.currentWidget(); }
