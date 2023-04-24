
#include "AppState.hpp"

AppState::AppState() {
    Component* component;
    for (unsigned i = 0; i < Component::COMPONENTS; i++)
        component = new Component(
            QString(Consts::NOT_SELECTED),
            static_cast<ComponentType>(i),
            QString(),
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
