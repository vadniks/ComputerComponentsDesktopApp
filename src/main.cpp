
#include <QApplication>
#include "ui/MainWindow.hpp"
#include "Consts.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(Consts::PC_ICON));
    MainWindow window;
    return QApplication::exec();
}
