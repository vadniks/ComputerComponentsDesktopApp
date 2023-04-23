
#pragma once

#include <QString>
#include <optional>
#include <utility>

using std::optional, std::initializer_list;

class Component final {
public:
    enum ComponentType : unsigned {
        CPU, MB, GPU,
        RAM, HDD, SSD,
        PSU, FAN, CASE
    };

    Component(
        QString&& title,
        ComponentType type,
        QString&& description,
        unsigned cost,
        optional<QString>&& image,
        unsigned id = INVALID_ID
    ) :
        title(std::move(title)),
        type(type),
        description(std::move(description)),
        cost(cost),
        image(std::move(image)),
        id(id)
    {}

    static const unsigned INVALID_ID = 0xffffffff;

    const unsigned id;
    const QString title;
    const ComponentType type;
    const QString description;
    const unsigned cost;
    const optional<QString> image;
};
