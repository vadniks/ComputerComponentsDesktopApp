
#pragma once

#include <QPushButton>
#include <QIcon>

class Util final {
private:
    inline Util() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    [[nodiscard]] static QPushButton* makeIconButton(const QString& icon);
};

#define BACK_ICON_BUTTON \
    ([this]() -> QPushButton* { \
        auto button = Util::makeIconButton(Consts::BACK_ICON); \
        connect(button, &QPushButton::clicked, this, [this](){ emit exitRequested(nullptr); }); \
        return button; \
    })()
