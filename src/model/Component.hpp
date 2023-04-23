
#pragma once

#include <QString>
#include <optional>
#include <utility>

using std::optional;

class Component final {
public:
    enum ComponentType : unsigned {
        CPU = 0, MB = 1, GPU = 2,
        RAM = 3, HDD = 4, SSD = 5,
        PSU = 6, FAN = 7, CASE = 8
    };

    Component(
        QString&& title,
        ComponentType type,
        QString&& description,
        unsigned cost,
        optional<QString>&& image,
        unsigned id = INVALID_ID
    );

    static QString typeTitle(ComponentType type);
    static QString typeImage(ComponentType type);

    static const unsigned INVALID_ID = 0xffffffff;

    const unsigned id;
    const QString title;
    const ComponentType type;
    const QString description;
    const unsigned cost;
    const optional<QString> image;
};
