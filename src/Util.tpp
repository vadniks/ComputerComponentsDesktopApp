
template<bool M, typename T, typename... Ts, typename>
T Util::minOrMax(T value, Ts... values) {
    const auto size = sizeof...(values) + 1;
    T array[size] = {value, values...};

    qsort(array, size, sizeof(T), [](const void* a, const void* b) -> int
    { return *(static_cast<const T*>(a)) - *(static_cast<const T*>(b)); });

    return M ? array[0] : array[size - 1];
}
