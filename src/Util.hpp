
#pragma once

#include <QPushButton>
#include <QIcon>

class Util final {
private:
    inline Util() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    [[nodiscard]] static QPushButton* makeIconButton(const QString& icon);
};
