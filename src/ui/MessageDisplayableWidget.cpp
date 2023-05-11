
#include <QtConcurrent/QtConcurrent>
#include <chrono>
#include <thread>
#include "MessageDisplayableWidget.hpp"
#include "../Consts.hpp"

MessageDisplayableWidget::MessageDisplayableWidget(QWidget* parent, QWidget* wrapped) :
    QWidget(parent), mBody(THIS_RETURNING_PROXY(cIsAlive = true)), mWrapped(wrapped)
{
    mMessage.setStyleSheet(u8R"(
        font-size: 18px;
        font-style: italic;
    )");

    mBody.addWidget(wrapped);
    mBody.addWidget(&mMessage, 0, Qt::AlignHCenter);
    mBody.setContentsMargins(0, 0, 0, 0);
}

void MessageDisplayableWidget::setWrappedWidget(QWidget* wrapped) {
    mBody.replaceWidget(mWrapped, wrapped);
    mWrapped = wrapped;
}

void MessageDisplayableWidget::showMessage(const QString& message, std::function<void ()>* callback) {
    mMessage.setText(message);

#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-result"

    QtConcurrent::run([this, callback](){
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        Util::switchThreads(this, &MessageDisplayableWidget::messageEnded, callback, cIsAlive);
    });

#   pragma clang diagnostic pop
}

void MessageDisplayableWidget::resizeEvent(QResizeEvent* event) {
    if (event) QWidget::resizeEvent(event);

    auto message = mMessage.text();
    if (!message.isEmpty()) mMessage.setText(
        mMessage.fontMetrics().elidedText(
            message,
            Qt::ElideRight,
            static_cast<int>(static_cast<float>(width()) * 0.95)
        )
    );
}

void MessageDisplayableWidget::messageEnded(void* callback) {
    mMessage.setText(Consts::EMPTY);

    auto callback2 = static_cast<std::function<void ()>*>(callback);
    callback2->operator()();
    delete callback2;
}

MessageDisplayableWidget::~MessageDisplayableWidget() { cIsAlive = false; }
