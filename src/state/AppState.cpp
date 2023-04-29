
#include <QtConcurrent/QtConcurrent>
#include "AppState.hpp"

AppState::AppState(MessageDispatcher::MessageDispatcherImpl&& messageDispatcherImpl) :
    mMessageDispatcher(std::move(messageDispatcherImpl))
{
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

QFuture<bool> AppState::authorized() {
    return QtConcurrent::run([this]() -> bool { return mNetwork.authorized(); });
}

QFuture<bool> AppState::logout() {
    return QtConcurrent::run([this]() -> bool { return mNetwork.deauthorize(); });
}

QFuture<QList<Component* _Nullable>* _Nullable> AppState::fetchSelectedComponents() {
    return QtConcurrent::run([this]() -> QList<Component*>* { return mNetwork.selectedComponents(); });
}

AppState::~AppState() { for (auto component : mSelectedComponents) delete component; }
