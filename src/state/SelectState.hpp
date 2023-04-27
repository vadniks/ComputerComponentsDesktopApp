
#pragma once

#include <QObject>
#include <QFuture>
#include "../model/Component.hpp"
#include "../model/Network.hpp"

class SelectState final : public QObject {
    Q_OBJECT
public:
    SelectState(QObject* parent, Component* target, Network& network);
    ~SelectState() override;
    [[nodiscard]] const QList<Component*>& fetchedComponents() const;
    [[nodiscard]] const Component* targetComponent();
    [[nodiscard]] const bool& hasFetched() const;
private:
    [[nodiscard]] QFuture<QList<Component*>*> fetchComponents(ComponentType type);

    QList<Component*> mFetchedComponents;
    bool mHasFetched;
    Component* mTargetComponent;
    const ComponentType mType;
    Network& mNetwork;
};
