
#include <QtConcurrent/QtConcurrent>
#include "LoginState.hpp"
#include "../model/Network.hpp"

QFuture<bool> LoginState::login(const QString& name, const QString& password)
{ return QtConcurrent::run([name, password]() -> bool {
    return Network::instance()->authorize(name, password);
}); }
