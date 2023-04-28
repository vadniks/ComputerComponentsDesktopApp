
#include "MessageDispatcher.hpp"

MessageDispatcher::MessageDispatcher(MessageDispatcherImpl&& messageDispatcherImpl) :
    mMessageDispatcherImpl(messageDispatcherImpl)
{
    if (cInstance) throw -1; // NOLINT(hicpp-exception-baseclass)
    cInstance = this;
}

MessageDispatcher* MessageDispatcher::instance() { return cInstance; }

void MessageDispatcher::dispatchMessage(const QString& message) { mMessageDispatcherImpl(message); }
