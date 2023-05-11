
#include "MainWindow.hpp"
#include "HomeWidget.hpp"
#include "SelectWidget.hpp"
#include "LoginWidget.hpp"
#include "AboutWidget.hpp"
#include "../Notifier.hpp"
#include "OrdersWidget.hpp"
#include "../Util.hpp"

MainWindow::MainWindow() :
    mAppState([this](
        const QString& message,
        std::function<void ()>* callback
    ) { mWidgetWrapper.showMessage(message, callback); }),
    mWrappedWidget(new HomeWidget(THIS_RETURNING_PROXY(cIsAlive = true), this, mAppState, false)),
    mWidgetWrapper(this, mWrappedWidget)
{
    connectHomeWidget();
    setCentralWidget(&mWidgetWrapper);

    setMinimumSize(Consts::APP_WIDTH, Consts::APP_HEIGHT);
    show();
}

#define IF(x, y) if (dynamic_cast<x ## Widget*>(mWrappedWidget)) return Widget::y;

IWindowShared::Widget MainWindow::currentWidget() const {
    IF(Home, HOME) else IF(Select, SELECT) else IF(About, ABOUT)
    else IF(Login, LOGIN) else IF(Orders, ORDERS) else throw -1;  // NOLINT(hicpp-exception-baseclass)
}

void MainWindow::connectHomeWidget() {
    auto widget = dynamic_cast<HomeWidget*>(mWrappedWidget);
    connect(widget, &HomeWidget::cartComponentSelected, this, &MainWindow::cartComponentTypeSelected);
    connect(widget, &HomeWidget::loginRequested, this, &MainWindow::loginRequested);
    connect(widget, &HomeWidget::infoRequested, this, &MainWindow::infoRequested);
    connect(widget, &HomeWidget::ordersRequested, this, &MainWindow::ordersRequested);
}

void MainWindow::replaceWidgetWith(QWidget* widget) {
    mWidgetWrapper.setWrappedWidget(widget);
    mWrappedWidget->disconnect();
    delete mWrappedWidget;
    mWrappedWidget = widget;
}

#define AUTHORIZED(x, y...) \
    mAppState.authorized().then([y](bool authorized){ \
        if (!authorized) { \
            MessageDispatcher::instance()->dispatchMessage(Consts::UNAUTHORIZED); \
            return; \
        } \
        x \
    });

void MainWindow::cartComponentTypeSelected(Component* component)
{ AUTHORIZED(Util::switchThreads(
    this,
    reinterpret_cast<void (MainWindow::*)(void*)>(&MainWindow::selectRequested),
    component,
    cIsAlive
);, this, component) }

void MainWindow::exitRequested(void* parameter) {
    if (parameter != nullptr) {
        auto result = static_cast<QPair<const Component*, Component*>*>(parameter);
        mAppState.replaceSelected(result->first, result->second);
        delete result;
    }

    auto widget = new HomeWidget(this, this, mAppState, dynamic_cast<LoginWidget*>(mWrappedWidget));
    replaceWidgetWith(widget);
    connectHomeWidget();
}

#define REPLACE_WIDGET(x, y...) \
    auto widget = new x ## Widget(y); \
    connect(widget, &x ## Widget::exitRequested, this, &MainWindow::exitRequested); \
    replaceWidgetWith(widget);

void MainWindow::loginRequested() { REPLACE_WIDGET(Login, this, this) }
void MainWindow::infoRequested() { REPLACE_WIDGET(About, this, this) }
void MainWindow::selectRequested(Component* component) { REPLACE_WIDGET(Select, this, this, component) }
void MainWindow::ordersRequested() { AUTHORIZED(Util::switchThreads(this, &MainWindow::ordersRequestedImpl, nullptr, cIsAlive);, this) }
void MainWindow::ordersRequestedImpl() { REPLACE_WIDGET(Orders, this, this); }

MainWindow::~MainWindow() {
    cIsAlive = false;
    delete mWrappedWidget;
}
