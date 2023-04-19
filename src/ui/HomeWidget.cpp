
#include "HomeWidget.hpp"

static QPushButton* c() {
    auto d = new QPushButton(QIcon(u8":/pc_icon.svg"), u8"");
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
