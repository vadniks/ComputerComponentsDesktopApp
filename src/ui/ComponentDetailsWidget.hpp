
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include "../model/Component.hpp"
#include "../model/Network.hpp"

class ComponentDetailsWidget final : public QWidget {
    Q_OBJECT
public:
    ComponentDetailsWidget(QWidget* parent, Network& network, Component* component);
    ~ComponentDetailsWidget() override;
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    Component* mCurrentComponent;
    QVBoxLayout mBody;
    QHBoxLayout mTitleCost;
    QHBoxLayout mImageDescription;
    QLabel mTitle;
    QLabel mCost;
    QLabel mImage;
    QScrollArea mScrollArea;
    QLabel mDescription;
    QHBoxLayout mButtons;
    QPushButton* mDone;
    QPushButton* mClose;
    QPixmap* mImagePixmap;
private slots:
    void imagePixmapUpdated(QPixmap* pixmap);
signals:
    void doneClicked(Component* target);
    void closeClicked();
};
