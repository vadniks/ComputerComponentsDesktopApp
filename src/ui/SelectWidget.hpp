
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/SelectState.hpp"
#include "ComponentDetailsWidget.hpp"

class SelectWidget final : public QWidget {
    Q_OBJECT

    enum Button { BACK, REMOVE };
public:
    SelectWidget(QWidget* parent, Component* target);
    ~SelectWidget() override;
private:
    SelectState mState;
    QVBoxLayout mBaseLayout;
    BaseComponentListWidget mComponentList;
    ComponentDetailsWidget* mDetails;

    QPushButton* makeIconButton(const QString& icon, Button which);
private slots:
    void iconButtonClicked(SelectWidget::Button button);
    void requestedDetailsForComponent(Component* component);
    void componentSelected(Component* component);
    void detailsRequestedExit();
signals:
    void exitRequested(void* parameter);
};
