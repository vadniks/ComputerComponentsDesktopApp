
#include "MainWindow.hpp"

MainWindow::MainWindow() : mHomeWidget(this) {
    setCentralWidget(&mHomeWidget);
    show();
}

MainWindow::~MainWindow() {

}
