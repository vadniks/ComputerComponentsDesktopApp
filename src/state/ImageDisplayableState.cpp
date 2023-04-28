
#include <QtConcurrent/QtConcurrent>
#include "ImageDisplayableState.hpp"
#include "../model/Network.hpp"

QFuture<QPixmap* _Nullable> ImageDisplayableState::fetchImage(Component* component) {
    return QtConcurrent::run([component]() -> QPixmap* {
        if (!component or !component->image) throw -1; // NOLINT(hicpp-exception-baseclass)

        auto bytes = Network::instance()->image(*(component->image));
        if (!bytes) return nullptr;

        auto pixmap = new QPixmap(QPixmap::fromImage(QImage::fromData(*bytes)));
        delete bytes;
        return pixmap;
    });
}
