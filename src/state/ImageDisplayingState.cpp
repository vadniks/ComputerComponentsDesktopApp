
#include <QtConcurrent/QtConcurrent>
#include "ImageDisplayingState.hpp"

QFuture<QPixmap* _Nullable> ImageDisplayingState::fetchImage(Network& network, Component* component) {
    return QtConcurrent::run([&network, component]() -> QPixmap* {
        if (!component or !component->image) throw -1; // NOLINT(hicpp-exception-baseclass)

        auto bytes = network.image(*(component->image));
        if (!bytes) return nullptr;

        auto pixmap = new QPixmap(QPixmap::fromImage(QImage::fromData(*bytes)));
        delete bytes;
        return pixmap;
    });
}
