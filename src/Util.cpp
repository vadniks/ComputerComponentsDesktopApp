
#include "Util.hpp"
#include "Consts.hpp"

QPushButton* Util::makeIconButton(const QString& icon) {
    auto pushButton = new QPushButton(QIcon(icon), QString());
    pushButton->setFixedSize(Consts::ICON_SIZE, Consts::ICON_SIZE);
    pushButton->setFlat(true);
    pushButton->setIconSize(QSize(Consts::ICON_SIZE - 5, Consts::ICON_SIZE - 5));
    return pushButton;
}

const char8_t* Util::copyString(const char8_t* string, unsigned size) {
    auto newString = new char8_t[size]();
    for (unsigned i = 0; i < size; i++)
        newString[i] = string[i];
    return newString;
}

const char8_t* operator ""_u8h(const char8_t* string, unsigned long size) { return Util::copyString(string, size); }
