
#include <QtConcurrent/QtConcurrent>
#include <chrono>
#include <thread>
#include "MessageDisplayableWidget.hpp"
#include "../state/Notifier.hpp"
#include "../Consts.hpp"

MessageDisplayableWidget::MessageDisplayableWidget(QWidget* parent, QWidget* wrapped) :
    QWidget(parent), mBody(this), mWrapped(wrapped)
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

void MessageDisplayableWidget::showMessage(const QString& message) {
    mMessage.setText(message);

    auto notifier = new Notifier();
    connect(notifier, &Notifier::notify, this, &MessageDisplayableWidget::messageEnded);

    auto _ = QtConcurrent::run([notifier](){
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        emit notifier->notify(nullptr);
        delete notifier;
    });
}

void MessageDisplayableWidget::messageEnded() { mMessage.setText(Consts::EMPTY); }
