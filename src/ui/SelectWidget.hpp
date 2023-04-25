
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/SelectState.hpp"
#include "ComponentDetailsWidget.hpp"

class SelectWidget final : public QWidget {
    Q_OBJECT
public:
    SelectWidget(QWidget* parent, Component* target);
    ~SelectWidget() override;
private:
    SelectState mState;
    QVBoxLayout mBody;
    BaseComponentListWidget mComponentList;
    ComponentDetailsWidget* mDetails;
private slots:
    void requestedDetailsForComponent(Component* component);
    void componentSelected(Component* component);
    void detailsRequestedExit();
signals:
    void exitRequested(void* parameter);
};
