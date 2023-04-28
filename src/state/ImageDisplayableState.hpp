
#pragma once

#include <QFuture>
#include <QPixmap>
#include "../model/Component.hpp"

class ImageDisplayableState final {
public:
    static QFuture<QPixmap* _Nullable> fetchImage(Component* component);
};
