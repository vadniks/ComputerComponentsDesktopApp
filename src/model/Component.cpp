
#include "Component.hpp"
#include "../Consts.hpp"

Component::Component(
    const char8_t* title,
    ComponentType type,
    const char8_t* description,
    unsigned int cost,
    const char8_t* _Nullable image,
    const unsigned int* _Nullable id
) :
    id(id),
    title(title),
    type(type),
    description(description),
    cost(cost),
    image(image)
{}

#define SWITCH(x, y) { switch (x) { y } }
#define CASE(x, y) case x: return u8 ## #y;
#define CASE2(x, y) case x: return y;

const char8_t* Component::typeTitle(ComponentType type) SWITCH(type,
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

const char8_t* Component::typeImage(ComponentType type) SWITCH(type,
    CASE2(ComponentType::CPU, Consts::CPU_ICON_S)
    CASE2(ComponentType::MB, Consts::MB_ICON_S)
    CASE2(ComponentType::GPU, Consts::GPU_ICON_S)
    CASE2(ComponentType::RAM, Consts::RAM_ICON_S)
    CASE2(ComponentType::HDD, Consts::HDD_ICON_S)
    CASE2(ComponentType::SSD, Consts::SSD_ICON_S)
    CASE2(ComponentType::PSU, Consts::PSU_ICON_S)
    CASE2(ComponentType::FAN, Consts::FAN_ICON_S)
    CASE2(ComponentType::CASE, Consts::CASE_ICON_S)
)

Component::~Component() {
    delete title;
    delete description;
    delete image;
    delete id;
}
