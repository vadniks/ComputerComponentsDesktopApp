
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

void SelectState::componentSelected(unsigned id) {
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-result"

    QtConcurrent::run([id](){ Network::instance()->select(id); });

#   pragma clang diagnostic pop
}

QFuture<QList<Component*>*> SelectState::fetchComponents(ComponentType type) {
    return QtConcurrent::run([type]() -> QList<Component*>* { return Network::instance()->components(type); });
}

SelectState::~SelectState() {
    for (auto component : mFetchedComponents) delete component;
}
