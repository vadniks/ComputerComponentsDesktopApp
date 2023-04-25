
#pragma once

#include <cstring>
#include "Util.hpp"

#define U8_STRING(n, s, l) \
    inline static const char8_t* n ## _S = u8 ## #s; \
    inline static const char8_t* n() { return Util::copyString(n ## _S, l); }

#define INT(n, i) inline static const int n = i;

class Consts final {
private:
    inline Consts() { throw -1; } // NOLINT(hicpp-exception-baseclass)
public:
    U8_STRING(APP_NAME, Componenta, 10)
    U8_STRING(TITLE, Title, 5)
    U8_STRING(DESCRIPTION, Description, 11)
    U8_STRING(NOT_SELECTED, Not selected, 12)
    U8_STRING(COMPONENT_SELECTION, Component selection, 19)

    U8_STRING(DOLLAR_SIGN_WITH_ARG, $%1, 3)

    U8_STRING(PC_ICON, :/pc_icon.svg, 13)
    U8_STRING(CPU_ICON, :/pc_cpu.svg, 12)
    U8_STRING(MB_ICON, :/pc_mb.svg, 11)
    U8_STRING(GPU_ICON, :/pc_gpu.svg, 12)
    U8_STRING(RAM_ICON, :/pc_ram.svg, 12)
    U8_STRING(HDD_ICON, :/pc_hdd.svg, 12)
    U8_STRING(SSD_ICON, :/pc_ssd.svg, 12)
    U8_STRING(PSU_ICON, :/pc_psu.svg, 12)
    U8_STRING(FAN_ICON, :/pc_fan.svg, 12)
    U8_STRING(CASE_ICON, :/pc_case.svg, 13)
    U8_STRING(INFO_ICON, :/info.svg, 10)
    U8_STRING(LOGIN_ICON, :/login.svg, 11)
    U8_STRING(BACK_ICON, :/back.svg, 10)
    U8_STRING(DONE_ICON, :/done.svg, 10)
    U8_STRING(REMOVE_ICON, :/remove.svg, 12)

    INT(APP_WIDTH, 640)
    INT(APP_HEIGHT, 640)
    INT(ICON_SIZE, 30)
};

#undef U8_STRING
#undef INT
