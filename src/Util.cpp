
#include "Util.hpp"
#include "Consts.hpp"

QPushButton* Util::makeIconButton(const QString& icon) {
    auto pushButton = new QPushButton(QIcon(icon), QString());
    pushButton->setFixedSize(Consts::ICON_SIZE, Consts::ICON_SIZE);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(Consts::ICON_SIZE - 5, Consts::ICON_SIZE - 5));
    return pushButton;
}
