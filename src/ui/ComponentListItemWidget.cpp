
#include "ComponentListItemWidget.hpp"
#include "UIConsts.hpp"

ComponentListItemWidget::ComponentListItemWidget(
    QWidget* parent,
    const QIcon& icon,
    const QString& title,
    const QString& description,
    unsigned cost
) :
    QWidget(parent),
    mBaseLayout(this),
    mTitlesLayout(nullptr),
    mTitle(title),
    mDescription(description),
    mCost(QString::asprintf("$%u", cost))
{
    setContentsMargins(0, 0, 0, 0);

    mIcon.setPixmap(icon.pixmap(UIConsts::ICON_SIZE, UIConsts::ICON_SIZE));
    mTitle.setStyleSheet(u8R"(
        color: white;
        font-size: 14px;
    )");
    mDescription.setStyleSheet(u8"color: grey");
    mCost.setStyleSheet(u8"font-size: 14px");

    mTitlesLayout.addWidget(&mTitle);
    mTitlesLayout.addWidget(&mDescription);

    mBaseLayout.addWidget(&mIcon);
    mBaseLayout.addStretch();
    mBaseLayout.addLayout(&mTitlesLayout);
    mBaseLayout.addStretch();
    mBaseLayout.addWidget(&mCost);
}

QSize ComponentListItemWidget::sizeHint() const
{ return mBaseLayout.sizeHint(); }
