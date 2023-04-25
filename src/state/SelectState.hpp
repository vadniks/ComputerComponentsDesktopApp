
#pragma once

#include <QObject>
#include "../model/Component.hpp"

class SelectState final : public QObject {
    Q_OBJECT
public:
    SelectState(QObject* parent, Component* target);
    ~SelectState() override;
    [[nodiscard]] const QList<Component*>& fetchedComponents() const;
    [[nodiscard]] const Component* targetComponent();
    [[nodiscard]] const bool& hasFetched() const;
private:
    QList<Component*> mFetchedComponents;
    bool mHasFetched;
    Component* mTargetComponent;
    const ComponentType mType;
};
