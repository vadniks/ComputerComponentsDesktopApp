
#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include "AppBarWidget.hpp"

class [[maybe_unused]] LoginWidget final : public QWidget {
    Q_OBJECT
public:
    [[maybe_unused]] explicit LoginWidget(QWidget* parent);
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QVBoxLayout mBody;
    AppBarWidget mAppBar;
    QLabel mImage;
    QLabel mWelcome;
    QHBoxLayout mBodyProxy;
    QVBoxLayout mControls;
    QLineEdit mName;
    QLineEdit mPassword;
    QHBoxLayout mButtons;
    QPushButton mProceed;
    QPushButton mClear;
private slots:
    void proceedClicked();
    void clearClicked();
signals:
    void exitRequested(void* parameter);
};
