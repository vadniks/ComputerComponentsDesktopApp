
#include "Component.hpp"

Component::Component(
    QString&& title,
    ComponentType type,
    QString&& description,
    unsigned int cost,
    optional<QString>&& image,
    unsigned int id
) :
    title(std::move(title)),
    type(type),
    description(std::move(description)),
    cost(cost),
    image(std::move(image)),
    id(id)
{}

#define SWITCH(x, y) { switch (x) { y } }
#define CASE(x, y) case x: return u8 ## #y;

QString Component::typeTitle(ComponentType type) SWITCH(type,
    CASE(ComponentType::CPU, Processor)
    CASE(ComponentType::MB, Motherboard)
    CASE(ComponentType::GPU, Graphics adapter)
    CASE(ComponentType::RAM, Operating memory)
    CASE(ComponentType::HDD, Hard drive)
    CASE(ComponentType::SSD, Solid state drive)
    CASE(ComponentType::PSU, Power supply unit)
    CASE(ComponentType::FAN, Cooler)
    CASE(ComponentType::CASE, Case)
)

QString Component::typeImage(ComponentType type) {
    return QString();
}
