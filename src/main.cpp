
#include <QApplication>
#include "ui/MainWindow.hpp"
#include "Consts.hpp"

#ifndef __clang__
#   pragma message("Usage of different compiler may cause compile errors as the project uses CLang's nullability checks (_Nullable)")
#endif

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(Consts::PC_ICON));
    MainWindow window;
    return QApplication::exec();
}
