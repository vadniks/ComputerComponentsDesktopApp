
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include "../model/Component.hpp"
#include "AppBarWidget.hpp"

class SelectWidget final : public QWidget {
    Q_OBJECT
public:
    SelectWidget(QWidget* parent, Component* target);
private:
    Component* mTargetComponent;
    AppBarWidget mAppBar;
    QVBoxLayout mBaseLayout;
    QListView mListView;
};
