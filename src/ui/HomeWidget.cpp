
#include "HomeWidget.hpp"

#include <QFile>

static QByteArray a() {
    QFile file(":/pc_icon.svg");
    file.open(QIODevice::ReadOnly);
    auto b = file.readAll();
    file.close();
    return b; // TODO
}

static QPushButton* c() {
    auto d = new QPushButton(QIcon(QPixmap::fromImage(QImage::fromData(a()))), u8"");
    d->setFixedSize(50, 50);
    d->setFlat(true);
    d->setIconSize(QSize(40, 40)); // TODO: this is just a test, will be cleaned up
    return d;
}

QPushButton* HomeWidget::e() {
    auto a = c();
    connect(a, &QPushButton::clicked, this, &HomeWidget::f);
    return a;
}

#include <QDebug>

void HomeWidget::f() {
    qDebug() << "fcedcfed"; // TODO
}

HomeWidget::HomeWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, u8"Title", { e() }),
    mListView(this)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListView);
}

HomeWidget::~HomeWidget() {

}
