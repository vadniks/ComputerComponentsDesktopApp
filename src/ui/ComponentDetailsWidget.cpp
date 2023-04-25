
#include "ComponentDetailsWidget.hpp"
#include "../Consts.hpp"
#include "../Util.hpp"

ComponentDetailsWidget::ComponentDetailsWidget(QWidget* parent, Component* component) :
    QWidget(parent),
    mCurrentComponent(component),
    mBaseLayout(this),
    mTitleCostLayout(nullptr),
    mImageDescriptionLayout(nullptr),
    mTitle(component->title),
    mCost(QString(Consts::DOLLAR_SIGN_WITH_ARG).arg(component->cost)),
    mScrollArea(this),
    mDescription(component->description),
    mButtonsLayout(nullptr),
    mDone(Util::makeIconButton(Consts::DONE_ICON)),
    mClose(Util::makeIconButton(Consts::REMOVE_ICON))
{
    mTitle.setStyleSheet(u8"font-size: 18px");
    mCost.setStyleSheet(u8R"(
        font-size: 18px;
        font-weight: bold;
    )");

    mTitleCostLayout.addWidget(&mTitle, 0, Qt::AlignLeading);
    mTitleCostLayout.addWidget(&mCost, 0, Qt::AlignTrailing);
    mTitleCostLayout.setContentsMargins(0, 0, 0, 0);

    mDescription.setWordWrap(true);
    mScrollArea.setWidget(&mDescription);
    mScrollArea.setWidget(nullptr);

    mImageDescriptionLayout.addWidget(&mImage, 0, Qt::AlignLeading);
    mImageDescriptionLayout.addWidget(&mScrollArea, 0, Qt::AlignTrailing);
    mImageDescriptionLayout.setContentsMargins(0, 0, 0, 0);

    mButtonsLayout.addStretch();
    mButtonsLayout.addWidget(mDone);
    mButtonsLayout.addWidget(mClose);
    mButtonsLayout.addStretch();
    mButtonsLayout.setContentsMargins(0, 0, 0, 0);

    mBaseLayout.addLayout(&mTitleCostLayout);
    mBaseLayout.addLayout(&mImageDescriptionLayout);
    mBaseLayout.addLayout(&mButtonsLayout);
    mBaseLayout.setContentsMargins(0, 0, 0, 0);

    connect(mDone, &QPushButton::clicked, this, [this](){ doneClicked(mCurrentComponent); });
    connect(mClose, &QPushButton::clicked, this, &ComponentDetailsWidget::closeClicked);

    this->resizeEvent(nullptr);
}

void ComponentDetailsWidget::resizeEvent([[maybe_unused]] QResizeEvent* event) {
    QWidget::resizeEvent(event);

    int reducedHeight = static_cast<int>(static_cast<float>(parentWidget()->height()) * 0.4f),
        width = parentWidget()->width(),
        layoutsHeight = mTitleCostLayout.sizeHint().height() + mButtonsLayout.sizeHint().height();
    setMaximumHeight(reducedHeight + layoutsHeight);

    auto metrics = QFontMetrics(mTitle.font());
    mTitle.setText(metrics.elidedText(
        mCurrentComponent->title,
        Qt::TextElideMode::ElideRight,
        width - mCost.width() - 40)
    );

    reducedHeight -= 10;
    mImage.setPixmap(QIcon(Component::typeImage(mCurrentComponent->type)).pixmap(reducedHeight)); // TODO
    mScrollArea.setFixedSize(width - 50 - reducedHeight, reducedHeight);
}

ComponentDetailsWidget::~ComponentDetailsWidget() {
    delete mDone;
    delete mClose;
}
