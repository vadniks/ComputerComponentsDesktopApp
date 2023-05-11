
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "AppBarWidget.hpp"
#include <QLabel>
#include <QHBoxLayout>
#include "AbsPrimaryWidget.hpp"

class AboutWidget final : public QWidget, public AbsPrimaryWidget {
    Q_OBJECT
public:
    AboutWidget(QWidget* parent, const IWindowShared* windowShared);
protected:
    void resizeEvent(QResizeEvent* event) override;
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
