
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
    mTitlesLayout.addWidget(&mTitle);
    mTitlesLayout.addWidget(&mDescription);

    mBaseLayout.addWidget(&mIcon);
    mBaseLayout.addLayout(&mTitlesLayout);
    mBaseLayout.addWidget(&mCost);
}

QSize ComponentListItem::sizeHint() const
{ return mBaseLayout.sizeHint(); }
