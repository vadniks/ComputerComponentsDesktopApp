
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class MessageDisplayableWidget final : public QWidget {
    Q_OBJECT
public:
    MessageDisplayableWidget(QWidget* parent, QWidget* wrapped);
    void setWrappedWidget(QWidget* wrapped);
    void showMessage(const QString& message, std::function<void ()>* callback);
protected:
    void resizeEvent(QResizeEvent* event) override;
private slots:
    void messageEnded(void* callback);
private:
    QVBoxLayout mBody;
    QWidget* mWrapped;
    QLabel mMessage;
};
