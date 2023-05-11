
#include <QApplication>
#include "ui/MainWindow.hpp"
#include "Consts.hpp"

#ifndef __clang__
#   pragma message("Usage of different compiler may cause compile errors as the project uses CLang's nullability checks (_Nullable)")
#endif

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    auto palette = QPalette(); // TODO: add animations and progress bars
    palette.setColor(QPalette::Window, QColor(40, 46, 51));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(24, 25, 29));
    palette.setColor(QPalette::AlternateBase, QColor(40, 46, 51));
    palette.setColor(QPalette::ToolTipBase, Qt::black);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(40, 46, 51));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::HighlightedText, Qt::black);

    QApplication::setStyle(u8"Fusion");
    QApplication::setPalette(palette);

    QApplication::setWindowIcon(QIcon(Consts::PC_ICON));
    MainWindow window;
    return QApplication::exec();
}
