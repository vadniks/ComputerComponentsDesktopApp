
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
    mTitle.setStyleSheet(u8"font-size: 18px");
    mCost.setStyleSheet(u8R"(
        font-size: 18px;
        font-weight: bold;
    )");

    mImage.setPixmap(QIcon(Component::typeImage(component->type)).pixmap(250, 250));

    mTitleCostLayout.addWidget(&mTitle, 0, Qt::AlignLeading);
    mTitleCostLayout.addWidget(&mCost, 0, Qt::AlignTrailing);

    mImageDescriptionLayout.addWidget(&mImage, 0, Qt::AlignLeading);
    mImageDescriptionLayout.addWidget(&mDescription, 0, Qt::AlignTrailing);

    mBaseLayout.addLayout(&mTitleCostLayout);
    mBaseLayout.addLayout(&mImageDescriptionLayout);
}
