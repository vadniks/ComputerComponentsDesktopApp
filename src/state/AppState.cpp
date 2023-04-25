
#include "AppState.hpp"
#include "../Util.hpp"

AppState::AppState() {
    Component* component;
    for (unsigned i = 0; i < Component::COMPONENTS; i++)
        component = new Component(
            Consts::NOT_SELECTED(),
            static_cast<ComponentType>(i),
            u8""_u8h,
            i
        ),
        mSelectedComponents.push_back(component);
}

QWidget* AppState::currentWidget() { return mCurrentWidget; }

void AppState::setCurrentWidget(QWidget* widget) { mCurrentWidget = widget; }

const QList<Component*>& AppState::selectedComponents() const { return mSelectedComponents; }

AppState::~AppState() {
    for (auto component : mSelectedComponents) delete component;
}
