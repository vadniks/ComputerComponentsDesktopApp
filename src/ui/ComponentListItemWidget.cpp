
#include "ComponentListItemWidget.hpp"
#include "UIConsts.hpp"

ComponentListItemWidget::ComponentListItemWidget(QWidget* parent, Component* component) :
    QWidget(parent),
    mBaseLayout(this),
    mTitlesLayout(nullptr),
    mTitle(component->title),
    mDescription(Component::typeTitle(component->type)),
    mCost(QString(u8"$%1").arg(component->cost))
{
    setContentsMargins(0, 0, 0, 0);

    if (!component->image)
        mIcon.setPixmap(QIcon(UIConsts::PC_ICON).pixmap(UIConsts::ICON_SIZE, UIConsts::ICON_SIZE));
    else {/*TODO*/}

    mTitle.setStyleSheet(u8R"(
        color: white;
        font-size: 14px;
    )");

    mDescription.setStyleSheet(u8"color: grey");
    mCost.setStyleSheet(u8"font-size: 14px");

    mTitlesLayout.addWidget(&mTitle, 0, Qt::AlignCenter);
    mTitlesLayout.addWidget(&mDescription);

    mBaseLayout.addWidget(&mIcon);
    mBaseLayout.addStretch();
    mBaseLayout.addLayout(&mTitlesLayout);
    mBaseLayout.addStretch();
    mBaseLayout.addWidget(&mCost);
}

QSize ComponentListItemWidget::sizeHint() const
{ return mBaseLayout.sizeHint(); }
