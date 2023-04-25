
#include "AboutWidget.hpp"
#include "../Consts.hpp"
#include "../Util.hpp"

AboutWidget::AboutWidget(QWidget* parent) :
    QWidget(parent),
    mBody(this),
    mAppBar(this, Consts::APP_NAME, new QString(Consts::SLOGAN), {}, BACK_ICON_BUTTON),
    mAbout(Consts::ABOUT_TEXT),
    mCopyright(Consts::COPYRIGHT)
{
    mImages.addWidget(&mHardware);
    mImages.addWidget(&mQuality);

    mBody.addWidget(&mAppBar, 0, Qt::AlignTop);
    mBody.addWidget(&mAbout);
    mBody.addLayout(&mImages);
    mBody.addWidget(&mCopyright, 0, Qt::AlignBottom);
}
