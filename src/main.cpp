
#include <QApplication>
#include "ui/MainWindow.hpp"
#include "Consts.hpp"

#ifndef __clang__
#   pragma message("Usage of different compiler may cause compile errors as the project uses CLang's nullability checks (_Nullable)")
#endif

#include "Util.hpp"

int main(int argc, char** argv) {
    printf("%d\n", Util::minOrMax<false>(11, 9, 1, 5, 8, 10, 3, 2)); // TODO: test only

    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(Consts::PC_ICON));
    MainWindow window;
    return QApplication::exec();
}
