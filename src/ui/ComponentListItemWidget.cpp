
#include "ComponentListItemWidget.hpp"
#include "../Consts.hpp"

static QPixmap makeTypedStubIconPixmap(ComponentType type)
{ return QIcon(Component::typeImage(type)).pixmap(Consts::ICON_SIZE, Consts::ICON_SIZE); }

ComponentListItemWidget::ComponentListItemWidget(QWidget* parent, Component* component) :
    QWidget(parent),
    mBaseLayout(this),
    mTitlesLayout(nullptr),
    mDescription(Component::typeTitle(component->type)),
    mCost(QString(Consts::DOLLAR_SIGN_WITH_ARG).arg(component->cost)),
    mTitleString(component->title)
{
    setContentsMargins(0, 0, 0, 0);

    if (!component->image)
        mIcon.setPixmap(makeTypedStubIconPixmap(component->type));
    else {/*TODO*/}

    mTitle.setStyleSheet(u8R"(
        color: white;
        font-size: 14px;
    )");

    mDescription.setStyleSheet(u8"color: grey");
    mCost.setStyleSheet(u8"font-size: 16px");

    mTitlesLayout.addWidget(&mTitle, 0, Qt::AlignCenter);
    mTitlesLayout.addWidget(&mDescription, 0, Qt::AlignCenter);

    mBaseLayout.addWidget(&mIcon);
    mBaseLayout.addStretch();
    mBaseLayout.addLayout(&mTitlesLayout);
    mBaseLayout.addStretch();
    mBaseLayout.addWidget(&mCost);
}

void ComponentListItemWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);

    mTitle.setMaximumSize(static_cast<signed>(static_cast<float>(window()->width()) * 0.75f), 50);
    QFontMetrics metrics(mTitle.font());
    mTitle.setText(metrics.elidedText(mTitleString, Qt::ElideRight, mTitle.maximumWidth()));
}

QSize ComponentListItemWidget::sizeHint() const
{ return mBaseLayout.sizeHint(); }
