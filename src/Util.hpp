
#pragma once

#include <QPushButton>
#include <QIcon>

class Util final {
private:
    inline Util() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    [[nodiscard]] static QPushButton* makeIconButton(const QString& icon);
    [[nodiscard]] static const char8_t* copyString(const char8_t* string, unsigned size);
};

[[nodiscard]] const char8_t* operator ""_u8h(const char8_t* string, unsigned long size);
