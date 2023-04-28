
#include <QtConcurrent/QtConcurrent>
#include "SelectState.hpp"
#include "../model/Network.hpp"

SelectState::SelectState(QObject* parent, Component* target) :
    QObject(parent), mTargetComponent(target), mType(target->type)
{
    fetchComponents(mType).then([this](QList<Component*>* components) {
        if (components)
            for (auto component : *components)
                mFetchedComponents.push_back(component);

        delete components;
        emit componentsFetched();
    });
}

const QList<Component*>& SelectState::fetchedComponents() const { return mFetchedComponents; }

const Component* SelectState::targetComponent() { return mTargetComponent; }

QFuture<QList<Component*>*> SelectState::fetchComponents(ComponentType type) {
    return QtConcurrent::run([type]() -> QList<Component*>* { return Network::instance()->components(type); });
}

SelectState::~SelectState() {
    for (auto component : mFetchedComponents) delete component;
}
