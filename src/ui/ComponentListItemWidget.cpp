
#include "ComponentListItemWidget.hpp"
#include "../Consts.hpp"
#include "../state/ImageDisplayableState.hpp"

static QPixmap makeTypedStubIconPixmap(ComponentType type)
{ return QIcon(Component::typeImage(type)).pixmap(Consts::ICON_SIZE, Consts::ICON_SIZE); }

ComponentListItemWidget::ComponentListItemWidget(QWidget* parent, Network& network, Component* component) :
    QWidget(parent),
    mBody(this),
    mTitles(nullptr),
    mDescription(Component::typeTitle(component->type)),
    mCost(QString(Consts::DOLLAR_SIGN_WITH_ARG).arg(component->cost)),
    mTitleString(component->title)
{
    setContentsMargins(0, 0, 0, 0);

    mIcon.setPixmap(makeTypedStubIconPixmap(component->type));

    if (component->image) ImageDisplayableState::fetchImage(network, component)
        .then([this](QPixmap* pixmap) {
            mIcon.setPixmap(pixmap->scaled(Consts::ICON_SIZE, Consts::ICON_SIZE));
            delete pixmap;
        });

    mTitle.setStyleSheet(u8R"(
        color: white;
        font-size: 14px;
    )");

    mDescription.setStyleSheet(u8"color: grey");
    mCost.setStyleSheet(u8"font-size: 16px");

    mTitles.addWidget(&mTitle, 0, Qt::AlignCenter);
    mTitles.addWidget(&mDescription, 0, Qt::AlignCenter);

    mBody.addWidget(&mIcon);
    mBody.addStretch();
    mBody.addLayout(&mTitles);
    mBody.addStretch();
    mBody.addWidget(&mCost);
}

void ComponentListItemWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);

    mTitle.setMaximumSize(static_cast<signed>(static_cast<float>(window()->width()) * 0.75f), 50);
    QFontMetrics metrics(mTitle.font());
    mTitle.setText(metrics.elidedText(mTitleString, Qt::ElideRight, mTitle.maximumWidth()));
}

QSize ComponentListItemWidget::sizeHint() const
{ return mBody.sizeHint(); }
