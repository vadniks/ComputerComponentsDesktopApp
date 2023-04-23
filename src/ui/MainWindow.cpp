
#include "MainWindow.hpp"
#include "UIConsts.hpp"

MainWindow::MainWindow() : mHomeWidget(this) {
    setCentralWidget(&mHomeWidget);
    setMinimumSize(UIConsts::APP_WIDTH, UIConsts::APP_HEIGHT);
    show();
}

MainWindow::~MainWindow() {

}
