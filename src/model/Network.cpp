
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
    cMainThreadId = std::make_optional(std::this_thread::get_id());
}

Network* Network::instance() { return cInstance; }

#define NON_EMPTY_LIST_OR_NULL \
    result and !result->empty() ? result : [result]() -> decltype(result) { delete result; return nullptr; }();

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

    return NON_EMPTY_LIST_OR_NULL
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

#define SET_RESULT_BY_REPLY_STATUS \
    if (reply->error() == QNetworkReply::NoError) { \
        auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute); \
        result = statusCode.isValid() and statusCode.toInt() == 200; \
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
        [&result](QNetworkReply* reply) { SET_RESULT_BY_REPLY_STATUS }
    );

    return result;
}

bool Network::authorized() {
    auto result = false;

    synchronize(
        [](QNetworkAccessManager& manager) {
            return manager.get(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/authorizedU")));
        },
        [&result](QNetworkReply* reply) { SET_RESULT_BY_REPLY_STATUS }
    );

    return result;
}

bool Network::deauthorize() {
    auto result = false;

    synchronize(
        [](QNetworkAccessManager& manager) {
            return manager.post(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/logout")), QByteArray());
        },
        [&result](QNetworkReply* reply) { SET_RESULT_BY_REPLY_STATUS }
    );

    return result;
}

QList<Component*>* Network::selectedComponents() {
    QList<Component*>* result = nullptr;

    synchronize(
        [](QNetworkAccessManager& manager) {
            return manager.get(QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/selected")));
        },
        [&result, this](QNetworkReply* reply) {
            if (reply->error() != QNetworkReply::NoError) return;
            if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200) return;

            auto selected = QString(reply->readAll()).split(',');
            if (selected.size() != Component::COMPONENTS) return;

            result = new QList<Component*>();
            for (unsigned i = 0; i < Component::COMPONENTS; i++) {
                bool isNotNull = true;
                auto id = selected[i].toInt(&isNotNull);
                result->push_back(isNotNull ? component(id) : nullptr);
            }
        }
    );

    return NON_EMPTY_LIST_OR_NULL
}

bool Network::select(unsigned int id) {
    bool result = false;

    synchronize(
        [id](QNetworkAccessManager& manager) {
            return manager.post(
                QNetworkRequest(QUrl(QString(u8"http://0.0.0.0:8080/select/%1").arg(id))), // TODO: extract server address constant
                QByteArray()
            );
        },
        [&result](QNetworkReply* reply) { SET_RESULT_BY_REPLY_STATUS }
    );

    return result;
}

bool Network::clearSelected() {
    bool result = false;

    synchronize(
        [](QNetworkAccessManager& manager) { return manager.post( // TODO: extract base post request schema into a functional method or into a macro
            QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/clearSelected")),
            QByteArray()
        ); },
        [&result](QNetworkReply* reply) { SET_RESULT_BY_REPLY_STATUS }
    );

    return result;
}

bool Network::submitOrder(
    const QString& firstName,
    const QString& lastName,
    const QString& phoneNumber,
    const QString& address
) {
    auto result = false, parsed = false;
    auto phone = phoneNumber.toInt(&parsed);
    if (!parsed) return false;

    synchronize(
        [&](QNetworkAccessManager& manager) { return manager.post(
            QNetworkRequest(QUrl(u8"http://0.0.0.0:8080/order")),
            QByteArray(QJsonDocument(QJsonObject({
                { u8"firstName", firstName },
                { u8"lastName", lastName },
                { u8"phone", phone },
                { u8"address", address }
            })).toJson())
        ); },
        [&result](QNetworkReply* reply) { SET_RESULT_BY_REPLY_STATUS }
    );

    return result;
}

QList<Component*>* _Nullable Network::history() {
    QList<Component*>* result = nullptr;

    synchronize(
        [](QNetworkAccessManager& manager) { return nullptr; },
        [](QNetworkReply* reply) {  }
    );

    return NON_EMPTY_LIST_OR_NULL
}

void Network::synchronize(
    const std::function<QNetworkReply* (QNetworkAccessManager&)>& asyncAction,
    const std::function<void (QNetworkReply*)>& resultHandler
) {
    assertNotMainThread();

    QNetworkAccessManager manager;
    manager.setCookieJar(&mCookieJar);

    QEventLoop loop;
    QObject::connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    QNetworkReply* futureResult = asyncAction(manager);
    loop.exec();

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

void Network::assertNotMainThread()
{ if (!cMainThreadId or std::this_thread::get_id() == cMainThreadId) throw -1; } // NOLINT(hicpp-exception-baseclass)
