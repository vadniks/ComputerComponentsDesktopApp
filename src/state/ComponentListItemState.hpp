
#pragma once

#include <QFuture>
#include <QPixmap>
#include "../model/Component.hpp"
#include "../model/Network.hpp"

class ComponentListItemState final {
public:
    static QFuture<QPixmap* _Nullable> fetchImage(Network& network, Component* component);
};
