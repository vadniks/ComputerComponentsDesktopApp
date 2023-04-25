
#include "ComponentDetailsWidget.hpp"
#include "../Consts.hpp"
#include "../Util.hpp"

ComponentDetailsWidget::ComponentDetailsWidget(QWidget* parent, Component* component) :
    QWidget(parent),
    mCurrentComponent(component),
    mBody(this),
    mTitleCost(nullptr),
    mImageDescription(nullptr),
    mTitle(component->title),
    mCost(QString(Consts::DOLLAR_SIGN_WITH_ARG).arg(component->cost)),
    mScrollArea(this),
    mDescription(component->description),
    mButtons(nullptr),
    mDone(Util::makeIconButton(Consts::DONE_ICON)),
    mClose(Util::makeIconButton(Consts::REMOVE_ICON))
{
    mTitle.setStyleSheet(u8"font-size: 18px");
    mCost.setStyleSheet(u8R"(
        font-size: 18px;
        font-weight: bold;
    )");

    mTitleCost.addWidget(&mTitle, 0, Qt::AlignLeading);
    mTitleCost.addWidget(&mCost, 0, Qt::AlignTrailing);
    mTitleCost.setContentsMargins(0, 0, 0, 0);

    mDescription.setWordWrap(true);
    mScrollArea.setWidget(&mDescription);
    mScrollArea.setWidget(nullptr);

    mImageDescription.addWidget(&mImage, 0, Qt::AlignLeading);
    mImageDescription.addWidget(&mScrollArea, 0, Qt::AlignTrailing);
    mImageDescription.setContentsMargins(0, 0, 0, 0);

    mButtons.addStretch();
    mButtons.addWidget(mDone);
    mButtons.addWidget(mClose);
    mButtons.addStretch();
    mButtons.setContentsMargins(0, 0, 0, 0);

    mBody.addLayout(&mTitleCost);
    mBody.addLayout(&mImageDescription);
    mBody.addLayout(&mButtons);
    mBody.setContentsMargins(0, 0, 0, 0);

    connect(mDone, &QPushButton::clicked, this, [this](){ doneClicked(mCurrentComponent); });
    connect(mClose, &QPushButton::clicked, this, &ComponentDetailsWidget::closeClicked);

    this->resizeEvent(nullptr);
}

void ComponentDetailsWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);

    int reducedHeight = static_cast<int>(static_cast<float>(parentWidget()->height()) * 0.4f),
        width = parentWidget()->width(),
        layoutsHeight = mTitleCost.sizeHint().height() + mButtons.sizeHint().height();
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
