
#include "ComponentDetailsWidget.hpp"
#include "../Consts.hpp"
#include "../Util.hpp"

ComponentDetailsWidget::ComponentDetailsWidget(QWidget* parent, const Component* component) :
    QWidget(parent),
    mCurrentComponent(component),
    mBaseLayout(this),
    mTitleCostLayout(nullptr),
    mButtonsLayout(nullptr),
    mTitleCostButtonsLayout(nullptr),
    mImageDescriptionLayout(nullptr),
    mDone(Util::makeIconButton(Consts::DONE_ICON)),
    mClose(Util::makeIconButton(Consts::REMOVE_ICON)),
    mTitle(component->title),
    mCost(QString(Consts::DOLLAR_SIGN_WITH_ARG).arg(component->cost)),
    mDescription(component->description)
{
    connect(mDone, &QPushButton::clicked, this, &ComponentDetailsWidget::doneClicked);
    connect(mClose, &QPushButton::clicked, this, &ComponentDetailsWidget::closeClicked);

    mButtonsLayout.addWidget(mDone);
    mButtonsLayout.addWidget(mClose);

    mTitle.setStyleSheet(u8"font-size: 18px");
    mCost.setStyleSheet(u8R"(
        font-size: 18px;
        font-weight: bold;
    )");

    mImage.setPixmap(QIcon(Component::typeImage(component->type)).pixmap(250, 250)); // TODO

    mTitleCostLayout.addWidget(&mTitle, 0, Qt::AlignLeading);
    mTitleCostLayout.addWidget(&mCost, 0, Qt::AlignTrailing);

    mTitleCostButtonsLayout.addLayout(&mTitleCostLayout);
    mTitleCostButtonsLayout.addLayout(&mButtonsLayout);

    mImageDescriptionLayout.addWidget(&mImage, 0, Qt::AlignLeading);
    mImageDescriptionLayout.addWidget(&mDescription, 0, Qt::AlignTrailing);

    mBaseLayout.addLayout(&mTitleCostButtonsLayout);
    mBaseLayout.addLayout(&mImageDescriptionLayout);
}

const Component* ComponentDetailsWidget::currentComponent() { return mCurrentComponent; }

ComponentDetailsWidget::~ComponentDetailsWidget() {
    delete mDone;
    delete mClose;
}
