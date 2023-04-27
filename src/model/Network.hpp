
#pragma once

#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include "Component.hpp"

class Network final : public QObject {
    Q_OBJECT
public:
    explicit Network(QObject* parent);
    QList<Component*>* _Nullable components();
private:
    QNetworkAccessManager mAccessManager;
    QNetworkCookieJar mCookieJar;
};
