
#pragma once

#include <QObject>

class Notifier final : public QObject {
    Q_OBJECT
public:
signals:
    void notify(void* object);
};
