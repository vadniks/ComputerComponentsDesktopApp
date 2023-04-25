
#pragma once

#include <QString>
#include <optional>

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
        std::optional<QString>&& image = std::nullopt,
        std::optional<unsigned>&& id = std::nullopt
    );

    static QString typeTitle(ComponentType type);
    static QString typeImage(ComponentType type);

    const std::optional<unsigned> id;
    const QString title;
    const ComponentType type;
    const QString description;
    const unsigned cost;
    const std::optional<QString> image;

    static const unsigned COMPONENTS = 9;
};

using ComponentType = Component::ComponentType;
