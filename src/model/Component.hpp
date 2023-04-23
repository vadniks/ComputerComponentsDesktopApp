
#pragma once

#include <QString>
#include <optional>
#include <utility>

using std::optional, std::nullopt;

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
        optional<QString>&& image = nullopt,
        optional<unsigned> id = nullopt
    );

    static QString typeTitle(ComponentType type);
    static QString typeImage(ComponentType type);

    const optional<unsigned> id;
    const QString title;
    const ComponentType type;
    const QString description;
    const unsigned cost;
    const optional<QString> image;
};
