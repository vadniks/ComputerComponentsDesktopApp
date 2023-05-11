
#pragma once

#include <QPushButton>
#include <QIcon>
#include <type_traits>

class Util final { public:
    Util() = delete;

    [[nodiscard]] static QPushButton* makeIconButton(const QString& icon);

    template<bool IsMin, typename T, typename... Ts, typename =
        std::enable_if_t<std::conjunction_v<std::is_arithmetic<Ts>..., std::is_same<Ts, T>...>>>
    [[nodiscard]] static T minOrMax(T value, Ts... values);

    static void notifySuccessfulOrFailed(bool successful);
    static QString makePlaceholderTextColorCss(const QPalette& palette);

    template<typename T, class C = std::remove_pointer_t<T>, typename S, typename = std::enable_if_t<
        std::is_pointer_v<T>
        and std::is_base_of_v<QObject, C>
        and (std::is_same_v<S, void (C::*)(void*)> or std::is_same_v<S, void (C::*)()>)>>
    static void switchThreads(T notifiedObject, S slot, void* _Nullable parameter, bool& isAlive);
};

#include "Util.tpp"

#define BACK_ICON_BUTTON \
    ([this]() -> QPushButton* { \
        auto button = Util::makeIconButton(Consts::BACK_ICON); \
        connect(button, &QPushButton::clicked, this, [this](){ emit exitRequested(nullptr); }); \
        return button; \
    })()

#define IS_ALIVE inline static bool cIsAlive = false;
#define THIS_RETURNING_PROXY(x) [this](){ x; return this; }()
