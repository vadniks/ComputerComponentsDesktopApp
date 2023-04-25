
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
    mAbout.setWordWrap(true);

    mImages.addStretch();
    mImages.addWidget(&mHardware, 0, Qt::AlignCenter);
    mImages.addWidget(&mQuality, 0, Qt::AlignCenter);
    mImages.addStretch();

    mBody.addWidget(&mAppBar, 0, Qt::AlignTop);
    mBody.addWidget(&mAbout);
    mBody.addStretch();
    mBody.addLayout(&mImages);
    mBody.addStretch();
    mBody.addWidget(&mCopyright, 0, Qt::AlignBottom | Qt::AlignHCenter);

    resizeEvent(nullptr);
}

void AboutWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);
    const auto size = static_cast<int>(static_cast<float>(Util::min(width(), height())) * 0.2);

    mHardware.setPixmap(QIcon(Consts::HARDWARE_ICON).pixmap(size));
    mQuality.setPixmap(QIcon(Consts::QUALITY_ICON).pixmap(static_cast<int>(static_cast<float>(size) * 1.5)));
}
