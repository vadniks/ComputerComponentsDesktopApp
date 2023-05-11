
#pragma once

#include "IWindowShared.hpp"

class AbsWidget {
public:
    explicit AbsWidget(const IWindowShared* windowShared)
        : mWindowShared(windowShared) {};
protected:
    const IWindowShared* mWindowShared;
};
