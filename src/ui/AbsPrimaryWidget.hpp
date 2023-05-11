
#pragma once

#include "IWindowShared.hpp"

class AbsPrimaryWidget {
public:
    explicit AbsPrimaryWidget(const IWindowShared* windowShared)
        : mWindowShared(windowShared) {};
protected:
    const IWindowShared* mWindowShared;
};
