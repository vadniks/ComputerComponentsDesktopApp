
#pragma once

class QString;

class LoginState {
public:
    static bool login(const QString& name, const QString& password);
};
