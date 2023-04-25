
#pragma once

#include <cstring>

#define U8_STRING(n, s) inline static const char8_t* n = u8 ## #s;
#define INT(n, i) inline static const int n = i;

class Consts final {
private:
    inline Consts() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    U8_STRING(APP_NAME, Componenta)
    U8_STRING(TITLE, Title)
    U8_STRING(DESCRIPTION, Description)
    U8_STRING(NOT_SELECTED, Not selected)
    U8_STRING(COMPONENT_SELECTION, Component selection)
    U8_STRING(EMPTY, )
    U8_STRING(LOGING_IN, Logging in)
    U8_STRING(PROCEED, Proceed)
    U8_STRING(CLEAR, Clear)
    U8_STRING(LOGIN, Login)
    U8_STRING(PASSWORD, Password)

    U8_STRING(DOLLAR_SIGN_WITH_ARG, $%1)

    U8_STRING(PC_ICON, :/pc_icon.svg)
    U8_STRING(CPU_ICON, :/pc_cpu.svg)
    U8_STRING(MB_ICON, :/pc_mb.svg)
    U8_STRING(GPU_ICON, :/pc_gpu.svg)
    U8_STRING(RAM_ICON, :/pc_ram.svg)
    U8_STRING(HDD_ICON, :/pc_hdd.svg)
    U8_STRING(SSD_ICON, :/pc_ssd.svg)
    U8_STRING(PSU_ICON, :/pc_psu.svg)
    U8_STRING(FAN_ICON, :/pc_fan.svg)
    U8_STRING(CASE_ICON, :/pc_case.svg)
    U8_STRING(INFO_ICON, :/info.svg)
    U8_STRING(LOGIN_ICON, :/login.svg)
    U8_STRING(BACK_ICON, :/back.svg)
    U8_STRING(DONE_ICON, :/done.svg)
    U8_STRING(REMOVE_ICON, :/remove.svg)

    INT(APP_WIDTH, 640)
    INT(APP_HEIGHT, 640)
    INT(ICON_SIZE, 30)
};

#undef U8_STRING
#undef INT
