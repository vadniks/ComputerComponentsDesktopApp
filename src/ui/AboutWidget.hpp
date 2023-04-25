
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "AppBarWidget.hpp"
#include <QLabel>
#include <QHBoxLayout>

class AboutWidget final : public QWidget {
    Q_OBJECT
public:
    explicit AboutWidget(QWidget* parent);
private:
    QVBoxLayout mBody;
    AppBarWidget mAppBar;
    QLabel mAbout;
    QHBoxLayout mImages;
    QLabel mHardware;
    QLabel mQuality;
    QLabel mCopyright;
signals:
    void exitRequested(void* parameter);
};
