
#include "Component.hpp"
#include "../ui//UIConsts.hpp"

Component::Component(
    QString&& title,
    ComponentType type,
    QString&& description,
    unsigned int cost,
    optional<QString>&& image,
    optional<unsigned> id
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
#define CASE2(x, y) case x: return y;

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

QString Component::typeImage(ComponentType type) SWITCH(type,
    CASE2(ComponentType::CPU, UIConsts::CPU_ICON)
    CASE2(ComponentType::MB, UIConsts::MB_ICON)
    CASE2(ComponentType::GPU, UIConsts::GPU_ICON)
    CASE2(ComponentType::RAM, UIConsts::RAM_ICON)
    CASE2(ComponentType::HDD, UIConsts::HDD_ICON)
    CASE2(ComponentType::SSD, UIConsts::SSD_ICON)
    CASE2(ComponentType::PSU, UIConsts::PSU_ICON)
    CASE2(ComponentType::FAN, UIConsts::FAN_ICON)
    CASE2(ComponentType::CASE, UIConsts::CASE_ICON)
)