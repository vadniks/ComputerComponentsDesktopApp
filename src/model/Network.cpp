
#include <QEventLoop>
#include "Network.hpp"

Network::Network(QObject* parent)
: mAccessManager(parent), mCookieJar(parent)
{ mAccessManager.setCookieJar(&mCookieJar); }

QList<Component*>* Network::components() {
    QEventLoop loop;
    connect(&mAccessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    QNetworkReply* reply = mAccessManager.get(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/component")));
    loop.exec();
    auto a = reply->error() == QNetworkReply::NoError ? new QList<Component*>(1) : nullptr;
    delete reply;
    return a;
}
