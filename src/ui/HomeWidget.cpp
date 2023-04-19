
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
    auto d = new QPushButton(u8"");
    d->setStyleSheet("border-image:url(:/pc_icon.svg);");
    d->setFixedSize(25, 25);
    return d;
}

HomeWidget::HomeWidget(QWidget* parent) :
    QWidget(parent),
    mBaseLayout(this),
    mAppBar(this, u8"Title", { c() }),
    mListView(this)
{
    mBaseLayout.addWidget(&mAppBar);
    mBaseLayout.addWidget(&mListView);
}

HomeWidget::~HomeWidget() {

}
