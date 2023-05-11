
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "BaseComponentListWidget.hpp"
#include "../state/SelectState.hpp"
#include "ComponentDetailsWidget.hpp"
#include "AbsPrimaryWidget.hpp"
#include "../Util.hpp"

class [[maybe_unused]] SelectWidget final : public QWidget, public AbsPrimaryWidget {
    Q_OBJECT
public:
    [[maybe_unused]] SelectWidget(QWidget* parent, const IWindowShared* windowShared, Component* target);
    ~SelectWidget() override;
private:
    IS_ALIVE
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
