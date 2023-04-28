
#pragma once

#include <QFuture>

class QString;

class LoginState {
public:
    static QFuture<bool> login(const QString& name, const QString& password);
};
