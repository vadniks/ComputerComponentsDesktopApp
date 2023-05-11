
#pragma once

class IWindowShared {
public:
    enum Widget { HOME, SELECT, ABOUT, LOGIN, ORDERS };
    [[nodiscard]] virtual Widget currentWidget() const = 0;
};
