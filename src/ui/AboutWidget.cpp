
#include "AboutWidget.hpp"
#include "../Consts.hpp"
#include "../Util.hpp"

[[maybe_unused]] AboutWidget::AboutWidget(QWidget* parent) :
    QWidget(parent),
    mBody(this),
    mAppBar(
        this,
        Consts::APP_NAME,
        new QString(Consts::SLOGAN),
        {},
        BACK_ICON_BUTTON
    ),
    mAbout(Consts::ABOUT_TEXT),
    mCopyright(Consts::COPYRIGHT)
{
    mImages.addWidget(&mHardware);
    mImages.addWidget(&mQuality);

    mBody.addWidget(&mAppBar, 0, Qt::AlignTop);
    mBody.addWidget(&mAbout);
    mBody.addLayout(&mImages);
    mBody.addWidget(&mCopyright, 0, Qt::AlignBottom);

    resizeEvent(nullptr);
}

void AboutWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);
    const auto size = static_cast<int>(static_cast<float>(Util::min(width(), height())) * 0.2);

    mHardware.setPixmap(QIcon(Consts::HARDWARE_ICON).pixmap(size));
    mQuality.setPixmap(QIcon(Consts::QUALITY_ICON).pixmap(size));
}
