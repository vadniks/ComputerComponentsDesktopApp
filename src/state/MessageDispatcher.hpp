
#pragma once

#include <functional>
#include <QQueue>

class QString;

class MessageDispatcher {
public:
    using MessageDispatcherImpl = std::function<void (const QString&, std::function<void ()>*)>;
    explicit MessageDispatcher(MessageDispatcherImpl&& messageDispatcherImpl);
    static MessageDispatcher* instance();
    void dispatchMessage(const QString& message);
    void messageDispatched();
private:
    void dispatchNext();

    MessageDispatcherImpl mMessageDispatcherImpl;
    QQueue<QString> mMessages;
    bool mDispatching = false;
    inline static MessageDispatcher* cInstance = nullptr;
};
