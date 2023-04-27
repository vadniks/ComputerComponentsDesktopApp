
#include <QtConcurrent/QtConcurrent>
#include "SelectState.hpp"

SelectState::SelectState(QObject* parent, Component* target, Network& network) :
    QObject(parent), mTargetComponent(target), mType(target->type), mNetwork(network)
{
    fetchComponents(mType).then([this](QList<Component*>* components) {
        qDebug() << components->size();
        for (auto component : *components) {
            qDebug() << component->toString();
            mFetchedComponents.push_back(component);
        }
        delete components;
        mHasFetched = true;
    });
}

const QList<Component*>& SelectState::fetchedComponents() const { return mFetchedComponents; }

const Component* SelectState::targetComponent() { return mTargetComponent; }

const bool& SelectState::hasFetched() const { return mHasFetched; }

QFuture<QList<Component*>*> SelectState::fetchComponents(ComponentType type) {
    return QtConcurrent::run([type, this]() -> QList<Component*>* { return mNetwork.components(type); });
}

SelectState::~SelectState() {
    for (auto component : mFetchedComponents) delete component;
}
