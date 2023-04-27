
#include "Network.hpp"

Network::Network(QObject* parent) : mAccessManager(parent), mCookieJar(parent) {
    mAccessManager.setCookieJar(&mCookieJar);
    connect(&mAccessManager, &QNetworkAccessManager::finished, this, &Network::replyReceived);
}

#include <QDebug>

void Network::components(QObject* handler, void (QObject::*callback)(QList<Component*>* _Nullable)) {
    auto receiver = new QObject();
    auto action = [callback, this, receiver, &handler](){
        qDebug() << "rgvfrtbfd";
        (handler->*callback)(new QList<Component*>());
        mAccessManager.disconnect(receiver);
        delete receiver;
    };

    QNetworkRequest request(QUrl(u8"http://0.0.0.0:8080/component"));
    connect(&mAccessManager, &QNetworkAccessManager::finished, receiver, action);
    mAccessManager.get(request);
}

void Network::replyReceived(QNetworkReply* reply) {

}
