
#include <QApplication>
#include "ui/MainWindow.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(u8":/pc_icon.svg")); // TODO: extract constant
    MainWindow window;
    return QApplication::exec();
}
