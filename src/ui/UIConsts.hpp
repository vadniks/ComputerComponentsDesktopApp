
#pragma once

#define U8_STRING static const char8_t*
#define INT static const int

class UIConsts final {
private:
    inline UIConsts() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    U8_STRING APP_NAME;

    U8_STRING PC_ICON;
    U8_STRING INFO_ICON;
    U8_STRING LOGIN_ICON;

    INT APP_WIDTH;
    INT APP_HEIGHT;
    INT ICON_SIZE;
};

#undef U8_STRING
#undef INT
