
#include "ComponentDetailsWidget.hpp"
#include "../Consts.hpp"

ComponentDetailsWidget::ComponentDetailsWidget(QWidget* parent, Component* component) :
    QWidget(parent),
    mBaseLayout(this),
    mTitleCostLayout(nullptr),
    mImageDescriptionLayout(nullptr),
    mTitle(component->title),
    mCost(QString(Consts::DOLLAR_SIGN_WITH_ARG).arg(component->cost)),
    mDescription(component->description)
{
    mImage.setPixmap(QIcon(Component::typeImage(component->type)).pixmap(50, 50));

    mTitleCostLayout.addWidget(&mTitle);
    mTitleCostLayout.addWidget(&mCost);

    mImageDescriptionLayout.addWidget(&mImage);
    mImageDescriptionLayout.addWidget(&mDescription);

    mBaseLayout.addLayout(&mTitleCostLayout);
    mBaseLayout.addLayout(&mImageDescriptionLayout);
}
