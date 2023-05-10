
#include "Util.hpp"
#include "Consts.hpp"
#include "state/MessageDispatcher.hpp"

QPushButton* Util::makeIconButton(const QString& icon) {
    auto pushButton = new QPushButton(QIcon(icon), QString());
    pushButton->setFixedSize(Consts::ICON_SIZE, Consts::ICON_SIZE);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(Consts::ICON_SIZE - 5, Consts::ICON_SIZE - 5));
    return pushButton;
}

void Util::notifySuccessfulOrFailed(bool successful)
{ MessageDispatcher::instance()->dispatchMessage(successful ? Consts::SUCCESSFUL : Consts::FAILED); }
