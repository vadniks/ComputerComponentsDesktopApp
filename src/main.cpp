
#include <QApplication>
#include "ui/MainWindow.hpp"
#include "ui/UIConsts.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(UIConsts::PC_ICON));
    MainWindow window;
    return QApplication::exec();
}
