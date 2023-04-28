
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QHttpMultiPart>
#include <QUrlQuery>
#include "Network.hpp"

Network::Network() {
    if (cInstance) throw -1; // NOLINT(hicpp-exception-baseclass)
    cInstance = this;
}

Network* Network::instance() { return cInstance; }

QList<Component*>* Network::components(ComponentType type) {
    QList<Component*>* result = nullptr;

    const auto parseComponents = [&result](const QByteArray& bytes) {
        if (!result) throw -1; // NOLINT(hicpp-exception-baseclass)
        const auto json = QJsonDocument::fromJson(bytes);

        for (const auto item : json.array())
            result->push_back(parseComponent(item.toObject()));
    };

    synchronize(
        [type](QNetworkAccessManager& manager) -> QNetworkReply* {
            return manager.get(QNetworkRequest(QUrl(QString(u8"http://0.0.0.0:8080/component/type/%1").arg(type))));
        },
        [&result, &parseComponents](QNetworkReply* reply) {
            if (reply->error() == QNetworkReply::NoError) {
                result = new QList<Component*>();
                parseComponents(reply->readAll());
            }
        }
    );

    qDebug() << "ervgfrdvg " << authorize(u8"user", u8"user"); // TODO: test only
    qDebug() << "rgvfrbfrg " << authorized();

    return result and !result->empty() ? result : nullptr;
}

Component* Network::component(unsigned id) {
    Component* result = nullptr;

    synchronize(
        [id](QNetworkAccessManager& manager) {
            return manager.get(
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

QByteArray* Network::image(const QString& imageString) {
    QByteArray* result = nullptr;

    synchronize(
        [imageString](QNetworkAccessManager& manager) {
            return manager.get(
                QNetworkRequest(QUrl(QString(u8"http://0.0.0.0:8080/res_back/%1.jpg").arg(imageString)))
            );
        },
        [&result](QNetworkReply* reply) {
            if (reply->error() == QNetworkReply::NoError)
                result = new QByteArray(reply->readAll());
        }
    );

    return result and !result->isEmpty() ? result : nullptr;
}

bool Network::authorize(const QString& name, const QString& password) {
    auto result = false;

    synchronize(
        [name, password](QNetworkAccessManager& manager) {
            auto request = QNetworkRequest(QUrl(QString(u8"http://0.0.0.0:8080/login")));
            request.setHeader(QNetworkRequest::ContentTypeHeader, QString(u8"application/x-www-form-urlencoded"));

            QUrlQuery query;
            query.addQueryItem(u8"name", name);
            query.addQueryItem(u8"password", password);

            return manager.post(request, query.toString(QUrl::FullyEncoded).toUtf8());
        },
        [&result](QNetworkReply* reply) {
            if (reply->error() == QNetworkReply::NoError) {
                auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                result = statusCode.isValid() and statusCode.toInt() == 200;
            }
        }
    );

    return result;
}

bool Network::authorized() {
    auto result = false;

    synchronize(
        [](QNetworkAccessManager& manager) {
            return manager.get(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/authorizedU")));
        },
        [&result](QNetworkReply* reply) {
            if (reply->error() == QNetworkReply::NoError) {
                auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                result = statusCode.isValid() and statusCode.toInt() == 200;
            }
        }
    );

    return result;
}

void Network::synchronize(
    const std::function<QNetworkReply* (QNetworkAccessManager&)>& asyncAction,
    const std::function<void (QNetworkReply*)>& resultHandler
) {
    QNetworkAccessManager manager;
    manager.setCookieJar(&mCookieJar);

    QEventLoop loop;
    QObject::connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    QNetworkReply* futureResult = asyncAction(manager);
    loop.exec(); // TODO: sigsegv when authorize() is called

    QObject::disconnect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
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
