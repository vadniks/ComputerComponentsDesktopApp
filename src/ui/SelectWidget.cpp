
#include "SelectWidget.hpp"
#include "../Util.hpp"

SelectWidget::SelectWidget(QWidget* parent, Component* target) :
    QWidget(parent),
    mTargetComponent(target),
    mBaseLayout(this),
    mComponentList(
        this,
        {[this]() -> QPushButton* {
            auto button = Util::makeIconButton(Consts::BACK_ICON);
            connect(button, &QPushButton::clicked, this, &SelectWidget::iconButtonClicked);
            return button;
        }()},
        mState.fetchedComponents()
    )
{
    mBaseLayout.addWidget(&mComponentList);
}

void SelectWidget::iconButtonClicked() {

}
