
#include "ComponentDetailsWidget.hpp"
#include "../Consts.hpp"

ComponentDetailsWidget::ComponentDetailsWidget(QWidget* parent, const Component* component) :
    QWidget(parent),
    mCurrentComponent(component),
    mBaseLayout(this),
    mTitleCostLayout(nullptr),
    mImageDescriptionLayout(nullptr),
    mTitle(component->title),
    mCost(QString(Consts::DOLLAR_SIGN_WITH_ARG).arg(component->cost)),
    mScrollArea(this),
    mDescription(component->description)
{
    mTitle.setStyleSheet(u8"font-size: 18px");
    mCost.setStyleSheet(u8R"(
        font-size: 18px;
        font-weight: bold;
    )");

    mTitleCostLayout.addWidget(&mTitle, 0, Qt::AlignLeading);
    mTitleCostLayout.addWidget(&mCost, 0, Qt::AlignTrailing);

    mDescription.setWordWrap(true);
    mScrollArea.setWidget(&mDescription);
    mScrollArea.setWidget(nullptr);

    mImageDescriptionLayout.addWidget(&mImage, 0, Qt::AlignLeading);
    mImageDescriptionLayout.addWidget(&mScrollArea, 0, Qt::AlignTrailing);

    mBaseLayout.addLayout(&mTitleCostLayout);
    mBaseLayout.addLayout(&mImageDescriptionLayout);

    this->resizeEvent(nullptr);
}

const Component* ComponentDetailsWidget::currentComponent() { return mCurrentComponent; }

void ComponentDetailsWidget::resizeEvent([[maybe_unused]] QResizeEvent* event) {
    int reducedHeight = static_cast<int>(static_cast<float>(parentWidget()->height()) * 0.4f);
    setMaximumHeight(reducedHeight);

    auto metrics = QFontMetrics(mTitle.font());
    mTitle.setText(metrics.elidedText(
        mCurrentComponent->title,
        Qt::TextElideMode::ElideRight,
        static_cast<int>(static_cast<float>(parentWidget()->width()) * 0.9f))
    );

    reducedHeight -= 50;
    mImage.setPixmap(QIcon(Component::typeImage(mCurrentComponent->type)).pixmap(reducedHeight)); // TODO
    mScrollArea.setFixedSize(parentWidget()->width() - 50 - reducedHeight, reducedHeight);
    mDescription.setMaximumHeight(reducedHeight);
}
