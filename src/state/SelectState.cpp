
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include "SelectState.hpp"
#include "../Consts.hpp"

static QFuture<QList<Component*>*> fetchComponents(ComponentType type) {
    return QtConcurrent::run([type]() -> QList<Component*>* {
        auto components = new QList<Component*>();
        for (unsigned i = 0; i < 10; i++) // TODO: test only
            components->push_back(new Component(Consts::TITLE, type, Consts::DESCRIPTION, i, std::nullopt, std::nullopt));
        return components;
    });
}

SelectState::SelectState(QObject* parent, Component* target) :
    QObject(parent), mTargetComponent(target), mType(target->type)
{
    fetchComponents(mType).then([this](QList<Component*>* components){
        for (auto component : *components) mFetchedComponents.push_back(component);
        delete components;
        mHasFetched = true;
    });
}

const QList<Component*>& SelectState::fetchedComponents() const { return mFetchedComponents; }

const bool& SelectState::hasFetched() const { return mHasFetched; }

SelectState::~SelectState() {
    for (auto component : mFetchedComponents) delete component;
}
