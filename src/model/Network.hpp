
#pragma once

#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <functional>
#include <type_traits>
#include "Component.hpp"

class Network final {
public:
    Network();
    QList<Component*>* _Nullable components();
private:
    template<typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
    void doInEventLoop(const std::function<T ()>& asyncAction, const std::function<void (T)>& resultHandler);

    QNetworkAccessManager mAccessManager;
    QNetworkCookieJar mCookieJar;
};
