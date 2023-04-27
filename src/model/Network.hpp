
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
    void components(QObject* handler, void (QObject::*callback)(QList<Component*>* _Nullable));
private slots:
    void replyReceived(QNetworkReply* reply);
private:
    QNetworkAccessManager mAccessManager;
    QNetworkCookieJar mCookieJar;
};
