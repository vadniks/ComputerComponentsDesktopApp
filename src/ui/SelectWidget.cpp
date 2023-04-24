
#include "SelectWidget.hpp"

SelectWidget::SelectWidget(QWidget* parent, Component* target) :
    QWidget(parent),
    mTargetComponent(target),
    mAppBar(this, u8"", {}),
    mBaseLayout(this)
{

}
