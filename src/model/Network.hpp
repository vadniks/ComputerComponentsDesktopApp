
#pragma once

#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <functional>
#include <optional>
#include <thread>
#include "Component.hpp"

class Network final {
public:
    Network();
    [[nodiscard]] static Network* instance();
    [[nodiscard]] QList<Component*>* _Nullable components(ComponentType type);
    [[nodiscard]] Component* _Nullable component(unsigned id);
    [[nodiscard]] QByteArray* _Nullable image(const QString& imageString);
    [[nodiscard]] bool authorize(const QString& name, const QString& password);
    [[nodiscard]] bool authorized();
    [[nodiscard]] bool deauthorize();
    [[nodiscard]] QList<Component* _Nullable>* _Nullable selectedComponents();
    [[nodiscard]] bool select(unsigned id);
private:
    void synchronize(
        const std::function<QNetworkReply* (QNetworkAccessManager&)>& asyncAction,
        const std::function<void (QNetworkReply*)>& resultHandler
    );
    [[nodiscard]] static Component* _Nullable parseComponent(const QJsonObject& json);
    [[nodiscard]] static std::optional<ComponentType> parseComponentType(const QString& typeTag);
    static void assertNotMainThread();

    QNetworkCookieJar mCookieJar;
    inline static Network* cInstance = nullptr;
    inline static std::optional<std::thread::id> cMainThreadId = std::nullopt;
};
