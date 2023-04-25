
#pragma once

class Component final {
public:
    enum ComponentType : unsigned {
        CPU = 0, MB = 1, GPU = 2,
        RAM = 3, HDD = 4, SSD = 5,
        PSU = 6, FAN = 7, CASE = 8
    };

    Component(
        const char8_t* _Nonnull title,
        ComponentType type,
        const char8_t* _Nonnull description,
        unsigned cost,
        const char8_t* _Nullable image = nullptr,
        const unsigned* _Nullable id = nullptr
    );
    ~Component();

    static const char8_t* _Nonnull typeTitle(ComponentType type);
    static const char8_t* _Nonnull typeImage(ComponentType type);

    const unsigned* _Nullable const id;
    const char8_t* _Nonnull const title;
    const ComponentType type;
    const char8_t* _Nonnull const description;
    const unsigned cost;
    const char8_t* _Nullable const image;

    static const unsigned COMPONENTS = 9;
};

using ComponentType = Component::ComponentType;
