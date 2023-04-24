
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/SelectState.hpp"

class SelectWidget final : public QWidget {
    Q_OBJECT

    enum Button { BACK, REMOVE };
public:
    SelectWidget(QWidget* parent, Component* target);
private:
    SelectState mState;
    QVBoxLayout mBaseLayout;
    BaseComponentListWidget mComponentList;

    QPushButton* makeIconButton(const QString& icon, Button which);
private slots:
    void iconButtonClicked(SelectWidget::Button button);
signals:
    void exitRequested(void* parameter);
};
