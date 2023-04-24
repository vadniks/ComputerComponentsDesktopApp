
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../model/AppState.hpp"

class HomeWidget final : public QWidget {
    Q_OBJECT

    enum Button : unsigned { INFO = 0, LOGIN = 1 };
public:
    HomeWidget(QWidget* parent, const AppState& state);
    QPushButton* makeIconButton(const QString& icon, Button button);
private slots:
    void iconButtonClicked(HomeWidget::Button button);
signals:
    void cartComponentSelected(Component* component);
private:
    QVBoxLayout mBaseLayout;
    BaseComponentListWidget mComponentList;
};
