
#include "HomeWidget.hpp"
//#include <QtSvgWidgets/QSvgWidget>
#include <QFile>

static QByteArray a() {
    QFile file(":/pc_icon.svg");
    file.open(QIODevice::ReadOnly);
    auto b = file.readAll();
    file.close();
    return b; // TODO
}

HomeWidget::HomeWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, u8"Title", { new QPushButton(QIcon(QPixmap::fromImage(QImage::fromData(a()))), u8"") }),
    mListView(this)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListView);
}

HomeWidget::~HomeWidget() {

}
