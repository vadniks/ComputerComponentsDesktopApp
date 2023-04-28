
#include "MainWindow.hpp"
#include "HomeWidget.hpp"
#include "SelectWidget.hpp"
#include "LoginWidget.hpp"
#include "AboutWidget.hpp"

#define REPLACE_WIDGET(x, y...) \
    auto widget = new x ## Widget(y); \
    connect(widget, &x ## Widget::exitRequested, this, &MainWindow::exitRequested); \
    replaceWidgetWith(widget);

MainWindow::MainWindow() :
    mAppState([this](const QString& message) { mWidgetWrapper.showMessage(message); }),
    mWrappedWidget(new HomeWidget(this, mAppState)), mWidgetWrapper(this, mWrappedWidget)
{
    connectHomeWidget();
    setCentralWidget(&mWidgetWrapper);

    setMinimumSize(Consts::APP_WIDTH, Consts::APP_HEIGHT);
    show();
}

void MainWindow::connectHomeWidget() {
    auto widget = dynamic_cast<HomeWidget*>(mWrappedWidget);
    connect(widget, &HomeWidget::cartComponentSelected, this, &MainWindow::cartComponentTypeSelected);
    connect(widget, &HomeWidget::loginRequested, this, &MainWindow::loginRequested);
    connect(widget, &HomeWidget::infoRequested, this, &MainWindow::infoRequested);
}

void MainWindow::replaceWidgetWith(QWidget* widget) {
    mWidgetWrapper.setWrappedWidget(widget);
    mWrappedWidget->disconnect();
    delete mWrappedWidget;
    mWrappedWidget = widget;
}

void MainWindow::cartComponentTypeSelected(Component* component)
{ REPLACE_WIDGET(Select, this, component) }

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

void MainWindow::loginRequested() { REPLACE_WIDGET(Login, this) }
void MainWindow::infoRequested() { REPLACE_WIDGET(About, this) }
MainWindow::~MainWindow() { delete mWrappedWidget; }
