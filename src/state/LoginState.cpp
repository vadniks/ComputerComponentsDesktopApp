
#include "LoginState.hpp"
#include "../model/Network.hpp"

bool LoginState::login(const QString& name, const QString& password)
{ return Network::instance()->authorize(/*name, password*/u8"user", u8"user"); } // TODO: SIGABRT free(): invalid pointer
