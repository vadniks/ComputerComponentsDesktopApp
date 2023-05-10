
#include <QtConcurrent/QtConcurrent>
#include "AppState.hpp"

AppState::AppState(MessageDispatcher::MessageDispatcherImpl&& messageDispatcherImpl) :
    mMessageDispatcher(std::move(messageDispatcherImpl)),
    mSelectedComponentsUpdateCallback(std::nullopt)
{
    Component* component;
    for (unsigned i = 0; i < Component::COMPONENTS; i++)
        component = makeStubComponent(i),
        mSelectedComponents.push_back(component);
}

const QList<Component*>& AppState::selectedComponents() const { return mSelectedComponents; }

void AppState::replaceSelected(const Component* old, Component* nw) {
    mSelectedComponents[mSelectedComponents.indexOf(old)] = nw;
    delete old;

    if (mSelectedComponentsUpdateCallback)
        mSelectedComponentsUpdateCallback->operator()();
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

void AppState::dropSelected() {
    for (unsigned i = 0; i < mSelectedComponents.size(); i++)
        replaceSelected(mSelectedComponents[i], makeStubComponent(i));
}

Component* AppState::makeStubComponent(unsigned index) {
    return new Component(
        Consts::NOT_SELECTED,
        static_cast<ComponentType>(index),
        Consts::EMPTY,
        0
    );
}

QFuture<bool> AppState::clearSelected() {
    return QtConcurrent::run([this]() -> bool { return mNetwork.clearSelected(); });
}

void AppState::setSelectedComponentsUpdateCallback(std::optional<std::function<void ()>>&& callback)
{ mSelectedComponentsUpdateCallback = std::move(callback); }

AppState::~AppState() { for (auto component : mSelectedComponents) delete component; }
