
#include "AppBarWidget.hpp"

AppBarWidget::AppBarWidget(
    QWidget* parent,
    const QString& title,
    const QString* _Nullable subtitle,
    QList<QPushButton*>&& buttons,
    QPushButton* _Nullable leftButton
) :
    QWidget(parent),
    mBody(this),
    mTitles(nullptr),
    mTitle(title),
    mSubtitle(subtitle ? new QLabel(*subtitle) : nullptr),
    mSubtitleText(subtitle),
    mButtons(nullptr),
    mButtonList(std::move(buttons)),
    mLeftButton(leftButton)
{
    mTitle.setStyleSheet(u8R"(
        font-size: 20px;
        font-style: italic;
        font-weight: bold;
    )");

    mTitles.addWidget(&mTitle);
    if (mSubtitle) mTitles.addWidget(mSubtitle);

    if (mLeftButton) mBody.addWidget(mLeftButton);
    mBody.addLayout(&mTitles);
    mBody.addLayout(&mButtons);

    for (auto button : mButtonList) mButtons.addWidget(button);

    setMaximumHeight(mTitles.sizeHint().height() + 10);
    resizeEvent(nullptr);
}

QList<QPushButton*>& AppBarWidget::buttonList() { return mButtonList; }

QHBoxLayout& AppBarWidget::buttons() { return mButtons; }

void AppBarWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);
    if (!mSubtitle) return;

    mSubtitle->setText(mSubtitle->fontMetrics().elidedText(
        *mSubtitleText,
        Qt::TextElideMode::ElideRight,
        width() - (mLeftButton ? mLeftButton->sizeHint().width() : 0) - mButtons.sizeHint().width() - 20
    ));
}

AppBarWidget::~AppBarWidget() {
    delete mSubtitle;
    delete mSubtitleText;
    for (auto button : mButtonList) delete button;
    delete mLeftButton;
}
