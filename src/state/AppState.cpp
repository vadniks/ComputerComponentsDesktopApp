
#include "AppState.hpp"

AppState::AppState(MessageDispatcher::MessageDispatcherImpl&& messageDispatcherImpl) : mMessageDispatcher(std::move(messageDispatcherImpl)) {
    Component* component;
    for (unsigned i = 0; i < Component::COMPONENTS; i++)
        component = new Component(
            Consts::NOT_SELECTED,
            static_cast<ComponentType>(i),
            Consts::EMPTY,
            i
        ),
        mSelectedComponents.push_back(component);
}

const QList<Component*>& AppState::selectedComponents() const { return mSelectedComponents; }

void AppState::replaceSelected(const Component* old, Component* nw) {
    mSelectedComponents[mSelectedComponents.indexOf(old)] = nw;
    delete old;
}

AppState::~AppState() {
    for (auto component : mSelectedComponents) delete component;
}
