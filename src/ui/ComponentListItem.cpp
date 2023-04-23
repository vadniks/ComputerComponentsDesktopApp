
#include "ComponentListItem.hpp"

ComponentListItem::ComponentListItem(
    QWidget* parent,
    const QIcon& icon,
    const QString& title,
    const QString& description,
    unsigned cost
) :
    QWidget(parent),
    mBaseLayout(this),
    mTitle(title),
    mDescription(description),
    mCost(QString::asprintf("%u", cost))
{
    setContentsMargins(0, 0, 0, 0);

    mIcon.setPixmap(icon.pixmap(25, 25));
    mTitle.setStyleSheet(u8"color: white");
    mDescription.setStyleSheet(u8"color: grey");

    mTitlesLayout.addWidget(&mTitle);
    mTitlesLayout.addWidget(&mDescription);

    mBaseLayout.addWidget(&mIcon);
    mBaseLayout.addStretch();
    mBaseLayout.addLayout(&mTitlesLayout);
    mBaseLayout.addStretch();
    mBaseLayout.addWidget(&mCost);
}

QSize ComponentListItem::sizeHint() const
{ return mBaseLayout.sizeHint(); }
