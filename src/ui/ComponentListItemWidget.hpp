
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "../model/Component.hpp"

class ComponentListItemWidget final : public QWidget {
    Q_OBJECT
public:
    ComponentListItemWidget(QWidget* parent, Component* component);
protected:
    void resizeEvent(QResizeEvent* event) override;
public:
    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] bool isFetching() const;
private slots:
    void imageFetched(void* pixmap);
private:
    QHBoxLayout mBody;
    QVBoxLayout mTitles;
    QLabel mIcon;
    QLabel mTitle;
    QLabel mDescription;
    QLabel mCost;
    const QString mTitleString;
    volatile bool mFetching = false;
};
