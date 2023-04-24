
#pragma once

#include <QObject>
#include "../model/Component.hpp"

class SelectState final : public QObject {
    Q_OBJECT
public:
    SelectState();
    ~SelectState() override;
    const QList<Component*>& fetchedComponents();
private:
    QList<Component*> mFetchedComponents;
};
