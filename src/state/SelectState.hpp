
#pragma once

#include <QObject>
#include <QFuture>
#include "../model/Component.hpp"

class SelectState final : public QObject {
    Q_OBJECT
public:
    SelectState(QObject* parent, Component* target);
    ~SelectState() override;
    [[nodiscard]] const QList<Component*>& fetchedComponents() const;
    [[nodiscard]] const Component* targetComponent();
private:
    [[nodiscard]] QFuture<QList<Component*>*> fetchComponents(ComponentType type);

    QList<Component*> mFetchedComponents;
    Component* mTargetComponent;
    const ComponentType mType;
signals:
    void componentsFetched();
};
