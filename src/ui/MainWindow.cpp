
#include "MainWindow.hpp"

MainWindow::MainWindow() {
    mAppState.currentWidget = new HomeWidget(this, mAppState);
    setCentralWidget(mAppState.currentWidget);
    setMinimumSize(Consts::APP_WIDTH, Consts::APP_HEIGHT);
    show();
}

MainWindow::~MainWindow() {

}
