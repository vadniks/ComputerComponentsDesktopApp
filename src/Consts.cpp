
#include "Consts.hpp"

#define U8_STRING_IMPL(n, s) const char8_t* Consts::n = u8 ## #s;
#define INT_IMPL(n, i) const int Consts::n = i;

U8_STRING_IMPL(APP_NAME, Componenta)
U8_STRING_IMPL(TITLE, Title)
U8_STRING_IMPL(DESCRIPTION, Description)
U8_STRING_IMPL(NOT_SELECTED, Not selected)

U8_STRING_IMPL(PC_ICON, :/pc_icon.svg)
U8_STRING_IMPL(CPU_ICON, :/pc_cpu.svg)
U8_STRING_IMPL(MB_ICON, :/pc_mb.svg)
U8_STRING_IMPL(GPU_ICON, :/pc_gpu.svg)
U8_STRING_IMPL(RAM_ICON, :/pc_ram.svg)
U8_STRING_IMPL(HDD_ICON, :/pc_hdd.svg)
U8_STRING_IMPL(SSD_ICON, :/pc_ssd.svg)
U8_STRING_IMPL(PSU_ICON, :/pc_psu.svg)
U8_STRING_IMPL(FAN_ICON, :/pc_fan.svg)
U8_STRING_IMPL(CASE_ICON, :/pc_case.svg)
U8_STRING_IMPL(INFO_ICON, :/info.svg)
U8_STRING_IMPL(LOGIN_ICON, :/login.svg)
U8_STRING_IMPL(BACK_ICON, :/back.svg)
U8_STRING_IMPL(DONE_ICON, :/done.svg)

INT_IMPL(APP_WIDTH, 640)
INT_IMPL(APP_HEIGHT, 640)
INT_IMPL(ICON_SIZE, 30)
