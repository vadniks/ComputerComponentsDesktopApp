
#include "HomeWidget.hpp"
#include <QFile>

static QPushButton* c() {
    auto d = new QPushButton(u8"");
    d->setStyleSheet("border-image:url(:/pc_icon.svg);");
    d->setFixedSize(25, 25);
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
