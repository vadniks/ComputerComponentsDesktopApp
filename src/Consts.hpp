
#pragma once

#define _U8_STRING_PREFIX(n) inline static const char8_t* n =
#define U8_STRING(n, s) _U8_STRING_PREFIX(n) u8 ## #s;
#define U8_STRING_2(n, s) _U8_STRING_PREFIX(n) s;
#define INT(n, i) inline static const int n = i;

class Consts final {
public:
    Consts() = delete;

    U8_STRING(APP_NAME, Componenta)
    U8_STRING(TITLE, Title)
    U8_STRING(DESCRIPTION, Description)
    U8_STRING(NOT_SELECTED, Not selected)
    U8_STRING(COMPONENT_SELECTION, Component selection)
    U8_STRING(EMPTY,)
    U8_STRING(LOGING_IN, Logging in)
    U8_STRING(PROCEED, Proceed)
    U8_STRING(CLEAR, Clear)
    U8_STRING(LOGIN, Login)
    U8_STRING(PASSWORD, Password)
    U8_STRING(WELCOME_ANON, Welcome Anonymous!)
    U8_STRING(SLOGAN, Build your own PC with PC Configurator online and free! Choose any components you like and buy them!)
    U8_STRING(COPYRIGHT, Copyright (C) 2022-2023 | All rights reserved)
    U8_STRING(NULL_STRING, null)
    U8_STRING(SUCCESSFUL, Successful)
    U8_STRING(FAILED, Failed)
    U8_STRING(TOTAL_COST, Total cost)
    U8_STRING(UNAUTHORIZED, Unauthorized)
    U8_STRING(HISTORY, History)
    U8_STRING(ORDERS, Orders)
    U8_STRING(SUBMIT_ORDER, Submit order)
    U8_STRING(FIRST_NAME, First name)
    U8_STRING(LAST_NAME, Last name)
    U8_STRING(PHONE_NUMBER, Phone number)
    U8_STRING(ADDRESS, Address)
    U8_STRING(SUBMIT, Submit)
    U8_STRING_2(ABOUT_TEXT, u8R"(We are Leading Company
Provide our customers with superior products and services at the most reasonable rates available. At the time of company formation in 2022, our core business was as a computer parts reseller. We initiated our company with the philosophy that “We refuse to compromise quality for profit” and have not since changed that guiding principle.
The quality of our custom built computers speak for themselves. They are reliable because we use brand name components which equals no headaches. PC Configurator sales and services focus on selling the best possible product at the best possible price. On a local level, PC Configurator’s exists to provide computer hardware and services. PC Configurator’s is very competitive on a national level in terms of price, quality and services. PC Configurator’s major market extends to all those with access to the internet and a web browser.
)")

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
    U8_STRING(HARDWARE_ICON, :/hwr_ico.svg)
    U8_STRING(QUALITY_ICON, :/qlt_ico.svg)
    U8_STRING(LOGOUT_ICON, :/logout.svg)

    INT(APP_WIDTH, 640)
    INT(APP_HEIGHT, 700)
    INT(ICON_SIZE, 30)
};

#undef _U8_STRING_PREFIX
#undef U8_STRING
#undef U8_STRING_2
#undef INT
