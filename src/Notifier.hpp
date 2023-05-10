
#pragma once

#include <QObject>

class Notifier final : public QObject {
    Q_OBJECT
signals:
    void notify(void* object);
};
