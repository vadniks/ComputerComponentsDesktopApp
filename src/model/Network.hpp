
#pragma once

#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <functional>
#include <optional>
#include "Component.hpp"

class Network final {
public:
    Network();
    static Network* instance();
    QList<Component*>* _Nullable components(ComponentType type);
    Component* _Nullable component(unsigned id);
    QByteArray* _Nullable image(const QString& imageString);
    bool authorize(const QString& name, const QString& password);
    bool authorized();
private:
    void synchronize(
        const std::function<QNetworkReply* (QNetworkAccessManager&)>& asyncAction,
        const std::function<void (QNetworkReply*)>& resultHandler
    );

    static Component* _Nullable parseComponent(const QJsonObject& json);
    static std::optional<ComponentType> parseComponentType(const QString& typeTag);

    QNetworkCookieJar mCookieJar;
    inline static Network* cInstance = nullptr;
};
