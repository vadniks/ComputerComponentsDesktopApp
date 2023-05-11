
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "AppBarWidget.hpp"
#include <QLabel>
#include <QHBoxLayout>
#include "AbsPrimaryWidget.hpp"
#include "../Util.hpp"

class AboutWidget final : public QWidget, public AbsPrimaryWidget {
    Q_OBJECT
public:
    AboutWidget(QWidget* parent, const IWindowShared* windowShared);
    ~AboutWidget() override;
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    IS_ALIVE
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
