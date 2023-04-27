
#include <QDebug>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonValue>
#include "Network.hpp"

Network::Network() { mAccessManager.setCookieJar(&mCookieJar); }

QList<Component*>* Network::components() {
    QList<Component*>* result = nullptr;
    doInEventLoop<QNetworkReply*>(
        [this]() -> QNetworkReply*
        { return mAccessManager.get(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/component/1"))); },
        [&result](QNetworkReply* reply){
            if (reply->error() == QNetworkReply::NoError) {
                result = new QList<Component*>(1);

                auto component = parseComponent(reply->readAll());
                qDebug() << component->toString();
                delete component;
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

Component* Network::parseComponent(const QByteArray& bytes) {
    auto json = QJsonDocument::fromJson(bytes);
    if (json.isEmpty()) return nullptr;

    auto type = parseComponentType(json[Component::TYPE].toString());
    if (!type) return nullptr;

    auto component = new Component(
        json[Component::TITLE].toString(),
        *type,
        json[Component::DESCRIPTION].toString(),
        static_cast<unsigned>(json[Component::COST].toInt()),
        std::make_optional(json[Component::IMAGE].toString()),
        std::make_optional(static_cast<unsigned>(json[Component::ID].toInt()))
    );

    return component;
}

#define IF(x) \
    if (typeTag == Component::typeTag(Component::x)) \
        return Component::x;

std::optional<ComponentType> Network::parseComponentType(const QString& typeTag) {
    IF(CPU) else IF(MB) else IF(GPU)
    else IF(RAM) else IF(HDD) else IF(SSD)
    else IF(PSU) else IF(FAN) else IF(CASE)
    else return std::nullopt;
}
