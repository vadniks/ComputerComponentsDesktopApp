
#pragma once

#include <QPushButton>
#include <QIcon>
#include <type_traits>

class Util final {
private:
    inline Util() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    [[nodiscard]] static QPushButton* makeIconButton(const QString& icon);

    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    [[nodiscard]] inline static T min(T a, T b) { return a < b ? a : b; }
};

#define BACK_ICON_BUTTON \
    ([this]() -> QPushButton* { \
        auto button = Util::makeIconButton(Consts::BACK_ICON); \
        connect(button, &QPushButton::clicked, this, [this](){ emit exitRequested(nullptr); }); \
        return button; \
    })()
