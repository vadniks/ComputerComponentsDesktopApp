
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

template<void* parameter, typename T, class C, typename S, typename>
void Util::synchronizeThreads(T notifiedObject, S slot) {
    Notifier notifier;

#   define PARAMS &notifier, &Notifier::notify, notifiedObject, slot
    QObject::connect(PARAMS);

    emit notifier.notify(parameter);

    QObject::disconnect(PARAMS);
#   undef PARAMS
}
