
#pragma once

#define U8_STRING static const char8_t*
#define INT static const int

class UIConsts final {
private:
    inline UIConsts() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    U8_STRING APP_NAME;
    U8_STRING TITLE;
    U8_STRING DESCRIPTION;

    U8_STRING PC_ICON;
    U8_STRING CPU_ICON;
    U8_STRING MB_ICON;
    U8_STRING GPU_ICON;
    U8_STRING RAM_ICON;
    U8_STRING HDD_ICON;
    U8_STRING SSD_ICON;
    U8_STRING PSU_ICON;
    U8_STRING FAN_ICON;
    U8_STRING CASE_ICON;
    U8_STRING INFO_ICON;
    U8_STRING LOGIN_ICON;

    INT APP_WIDTH;
    INT APP_HEIGHT;
    INT ICON_SIZE;
};

#undef U8_STRING
#undef INT
