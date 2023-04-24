
#pragma once

#include <QWidget>
#include <QList>
#include "Component.hpp"
#include "../Consts.hpp"

class AppState final {
public:
    AppState();
    ~AppState();
    QWidget* currentWidget();
    void setCurrentWidget(QWidget* widget);
    [[nodiscard]] const QList<Component*>& selectedComponents() const;
private:
    QWidget* mCurrentWidget = nullptr;
    QList<Component*> mSelectedComponents;
};
