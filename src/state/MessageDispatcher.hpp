
#pragma once

#include <functional>

class QString;

class MessageDispatcher {
public:
    using MessageDispatcherImpl = std::function<void (const QString&)>;
    explicit MessageDispatcher(MessageDispatcherImpl&& messageDispatcherImpl);
    static MessageDispatcher* instance();
    void dispatchMessage(const QString& message);
private:
    MessageDispatcherImpl mMessageDispatcherImpl;
    inline static MessageDispatcher* cInstance = nullptr;
};
