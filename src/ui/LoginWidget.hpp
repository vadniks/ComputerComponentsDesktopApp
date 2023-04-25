
#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include "AppBarWidget.hpp"

class LoginWidget final : public QWidget {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget* parent);
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QVBoxLayout mBaseLayout;
    AppBarWidget mAppBar;
    QLabel mImage;
    QLabel mWelcome;
    QHBoxLayout mBodyProxyLayout;
    QVBoxLayout mControlsLayout;
    QLineEdit mName;
    QLineEdit mPassword;
    QHBoxLayout mButtonsLayout;
    QPushButton mProceed;
    QPushButton mClear;
private slots:
    void proceedClicked();
    void clearClicked();
signals:
    void exitRequested(void* parameter);
};
