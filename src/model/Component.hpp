
#pragma once

#include <QString>
#include <optional>

#define STRING(n, s) inline static const char8_t* n = u8 ## #s;
#define UINT(n, i) static const unsigned n = i;

class Component final {
public:
    enum ComponentType : unsigned {
        CPU = 0, MB = 1, GPU = 2,
        RAM = 3, HDD = 4, SSD = 5,
        PSU = 6, FAN = 7, CASE = 8
    };

    Component(
        QString title,
        ComponentType type,
        QString description,
        unsigned cost,
        std::optional<QString> image = std::nullopt,
        const std::optional<unsigned>& id = std::nullopt
    );
    QString toString();

    static QString typeTitle(ComponentType type);
    static QString typeImage(ComponentType type);
    static QString typeTag(ComponentType type);

    const std::optional<unsigned> id;
    const QString title;
    const ComponentType type;
    const QString description;
    const unsigned cost;
    const std::optional<QString> image;

    UINT(COMPONENTS, 9)
    UINT(FIELDS, 6)

    STRING(ID, id)
    STRING(TITLE, title)
    STRING(TYPE, type)
    STRING(DESCRIPTION, description)
    STRING(COST, cost)
    STRING(IMAGE, image)
};

#undef STRING
#undef UINT

using ComponentType = Component::ComponentType;
