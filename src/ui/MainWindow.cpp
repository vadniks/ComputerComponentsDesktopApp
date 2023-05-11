
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
    mWrappedWidget(new HomeWidget(THIS_RETURNING_PROXY(cIsAlive = true), mAppState, false)),
    mWidgetWrapper(this, mWrappedWidget)
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

    auto widget = new HomeWidget(this, mAppState, dynamic_cast<LoginWidget*>(mWrappedWidget));
    replaceWidgetWith(widget);
    connectHomeWidget();
}

#define REPLACE_WIDGET(x, y...) \
    auto widget = new x ## Widget(y); \
    connect(widget, &x ## Widget::exitRequested, this, &MainWindow::exitRequested); \
    replaceWidgetWith(widget);

void MainWindow::loginRequested() { REPLACE_WIDGET(Login, this) }
void MainWindow::infoRequested() { REPLACE_WIDGET(About, this) }
void MainWindow::selectRequested(Component* component) { REPLACE_WIDGET(Select, this, component) }
void MainWindow::ordersRequested() { AUTHORIZED(Util::switchThreads(this, &MainWindow::ordersRequestedImpl, nullptr, cIsAlive);, this) }
void MainWindow::ordersRequestedImpl() { REPLACE_WIDGET(Orders, this); }

MainWindow::~MainWindow() {
    cIsAlive = false;
    delete mWrappedWidget;
}
