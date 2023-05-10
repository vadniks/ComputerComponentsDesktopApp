
#pragma once

#include <QPushButton>
#include <QIcon>
#include <type_traits>

class Util final {
public:
    Util() = delete;

    [[nodiscard]] static QPushButton* makeIconButton(const QString& icon);

    template<bool IsMin, typename T, typename... Ts, typename =
        std::enable_if_t<std::conjunction_v<std::is_arithmetic<Ts>..., std::is_same<Ts, T>...>>>
    [[nodiscard]] static T minOrMax(T value, Ts... values);

    static void notifySuccessfulOrFailed(bool successful);
};

#include "Util.tpp"

#define BACK_ICON_BUTTON \
    ([this]() -> QPushButton* { \
        auto button = Util::makeIconButton(Consts::BACK_ICON); \
        connect(button, &QPushButton::clicked, this, [this](){ emit exitRequested(nullptr); }); \
        return button; \
    })()
