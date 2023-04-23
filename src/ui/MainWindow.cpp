
#include <QDebug>
#include "MainWindow.hpp"
#include "HomeWidget.hpp"
#include "SelectWidget.hpp"

MainWindow::MainWindow() {
    mAppState.currentWidget = new HomeWidget(this, mAppState);
    connect(
        dynamic_cast<HomeWidget*>(mAppState.currentWidget),
        &HomeWidget::cartComponentSelected,
        this,
        &MainWindow::cartComponentTypeSelected
    );

    setCentralWidget(mAppState.currentWidget);
    setMinimumSize(Consts::APP_WIDTH, Consts::APP_HEIGHT);
    show();
}

void MainWindow::cartComponentTypeSelected(Component* component) {
    qDebug() << Component::typeTitle(component->type); // TODO

    auto widget = new SelectWidget(this, component);
    setCentralWidget(widget);

    mAppState.currentWidget->disconnect();
    delete mAppState.currentWidget;

    mAppState.currentWidget = widget;
}

MainWindow::~MainWindow() { delete mAppState.currentWidget; }
