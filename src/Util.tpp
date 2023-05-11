
#pragma once

#include <cstdlib>
#include "Notifier.hpp"

template<bool IsMin, typename T, typename... Ts, typename>
T Util::minOrMax(T value, Ts... values) {
    const auto size = sizeof...(values) + 1;
    T array[size] = {value, values...};

    qsort(array, size, sizeof(T), [](const void* a, const void* b) -> int
    { return *(static_cast<const T*>(a)) - *(static_cast<const T*>(b)); });

    return IsMin ? array[0] : array[size - 1];
}

template<typename T, class C, typename S, typename>
void Util::switchThreads(T notifiedObject, S slot, void* _Nullable parameter) {
    Notifier notifier;

#   define PARAMS &notifier, &Notifier::notify, notifiedObject, slot
    QObject::disconnect(PARAMS);
    QObject::connect(PARAMS);

    emit notifier.notify(parameter);

    QObject::disconnect(PARAMS);
#   undef PARAMS
}
