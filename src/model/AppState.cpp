
#include "AppState.hpp"

AppState::AppState() {
    Component* component;
    for (unsigned i = 0; i < Component::COMPONENTS; i++)
        component = new Component(
            QString(Consts::NOT_SELECTED),
            static_cast<ComponentType>(i),
            QString(),
            0
        ),
        selectedComponents.push_back(component);
}

AppState::~AppState() {
    for (auto component : selectedComponents) delete component;
}
