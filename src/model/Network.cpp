
#include <QDebug>
#include <QEventLoop>
#include "Network.hpp"

Network::Network() { mAccessManager.setCookieJar(&mCookieJar); }

QList<Component*>* Network::components() {
    QList<Component*>* result = nullptr;
    doInEventLoop<QNetworkReply*>(
        [this]() -> QNetworkReply*
        { return mAccessManager.get(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/component"))); },
        [&result](QNetworkReply* reply){
            if (reply->error() == QNetworkReply::NoError) {
                result = new QList<Component*>(1);
                qDebug() << QString(reply->readAll());
            }
        }
    );
    return result;
}

template<typename T, typename>
void Network::doInEventLoop(const std::function<T()>& asyncAction, const std::function<void(T)>& resultHandler) {
    QEventLoop loop;
    QObject::connect(&mAccessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    T futureResult = asyncAction();
    loop.exec();

    QObject::disconnect(&mAccessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    resultHandler(futureResult);
    delete futureResult;
}
