
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class MessageDisplayableWidget final : public QWidget {
    Q_OBJECT
public:
    MessageDisplayableWidget(QWidget* parent, QWidget* wrapped);
    void setWrappedWidget(QWidget* wrapped);
    void showMessage(const QString& message);
protected:
    void resizeEvent(QResizeEvent* event) override;
private slots:
    void messageEnded();
private:
    QVBoxLayout mBody;
    QWidget* mWrapped;
    QLabel mMessage;
};
