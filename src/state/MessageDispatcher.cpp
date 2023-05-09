
#include "MessageDispatcher.hpp"

MessageDispatcher::MessageDispatcher(MessageDispatcherImpl&& messageDispatcherImpl) :
    mMessageDispatcherImpl(messageDispatcherImpl)
{
    if (cInstance) throw -1; // NOLINT(hicpp-exception-baseclass)
    cInstance = this;
}

MessageDispatcher* MessageDispatcher::instance() { return cInstance; }

void MessageDispatcher::dispatchMessage(const QString& message) {
    mMessages.enqueue(message);
    if (!mDispatching) dispatchNext();
}

void MessageDispatcher::messageDispatched() {
    mDispatching = false;
    dispatchNext();
}

void MessageDispatcher::dispatchNext() {
    if (mMessages.isEmpty()) return;
    mDispatching = true;
    mMessageDispatcherImpl(mMessages.dequeue(), new std::function<void ()>([this](){ messageDispatched(); }));
}
