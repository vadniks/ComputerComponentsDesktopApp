
#pragma once

class Component final {
public:
    enum ComponentType : unsigned {
        CPU = 0, MB = 1, GPU = 2,
        RAM = 3, HDD = 4, SSD = 5,
        PSU = 6, FAN = 7, CASE = 8
    };

    Component(
        const char8_t* title,
        ComponentType type,
        const char8_t* description,
        unsigned cost,
        const char8_t* image = nullptr,
        const unsigned* id = nullptr
    );
    ~Component();

    static const char8_t* typeTitle(ComponentType type);
    static const char8_t* typeImage(ComponentType type);

    const unsigned* _Nullable const id;
    const char8_t* const title;
    const ComponentType type;
    const char8_t* const description;
    const unsigned cost;
    const char8_t* _Nullable const image;

    static const unsigned COMPONENTS = 9;
};

using ComponentType = Component::ComponentType;
