
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include "Network.hpp"

Network::Network() { mAccessManager.setCookieJar(&mCookieJar); }

QList<Component*>* Network::components() {
    QList<Component*>* result = nullptr;

    const auto parseComponents = [&result](const QByteArray& bytes) {
        if (!result) throw -1; // NOLINT(hicpp-exception-baseclass)
        const auto json = QJsonDocument::fromJson(bytes);

        for (const auto item : json.array())
            result->push_back(parseComponent(item.toObject()));
    };

    synchronize<QNetworkReply*>(
        [this]() -> QNetworkReply* {
            return mAccessManager.get(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/component")));
        },
        [&result, &parseComponents](QNetworkReply* reply) {
            if (reply->error() == QNetworkReply::NoError) {
                result = new QList<Component*>();
                parseComponents(reply->readAll());
            }
        }
    );

    return result and !result->empty() ? result : nullptr;
}

Component* Network::component(unsigned id) {
    Component* result = nullptr;

    synchronize<QNetworkReply*>(
        [this, id]() -> QNetworkReply* {
            return mAccessManager.get(
                QNetworkRequest(QUrl(QString(u8"http://0.0.0.0:8080/component/%1").arg(id)))
            );
        },
        [&result](QNetworkReply* reply) {
            if (reply->error() == QNetworkReply::NoError)
                result = parseComponent(QJsonDocument::fromJson(reply->readAll()).object());
        }
    );

    return result;
}

template<typename T, typename>
void Network::synchronize(const std::function<T ()>& asyncAction, const std::function<void (T)>& resultHandler) {
    QEventLoop loop;
    QObject::connect(&mAccessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    const T futureResult = asyncAction();
    loop.exec();

    QObject::disconnect(&mAccessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    resultHandler(futureResult);
    delete futureResult;
}

Component* Network::parseComponent(const QJsonObject& json) {
    if (json.isEmpty()) return nullptr;

    const auto type = parseComponentType(json[Component::TYPE].toString());
    if (!type) return nullptr;

    const auto component = new Component(
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
