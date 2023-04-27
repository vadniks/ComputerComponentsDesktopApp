
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/SelectState.hpp"
#include "ComponentDetailsWidget.hpp"

class [[maybe_unused]] SelectWidget final : public QWidget {
    Q_OBJECT
public:
    [[maybe_unused]] SelectWidget(QWidget* parent, Component* target, Network& network);
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
    void componentsFetched();
signals:
    void exitRequested(void* parameter);
};
