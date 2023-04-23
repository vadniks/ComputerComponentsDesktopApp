
#include "UIConsts.hpp"

#define U8_STRING_IMPL(n, s) const char8_t* UIConsts::n = u8 ## s;
#define INT_IMPL(n, i) const int UIConsts::n = i;

U8_STRING_IMPL(APP_NAME, "Componenta")

U8_STRING_IMPL(PC_ICON, ":/pc_icon.svg")
U8_STRING_IMPL(INFO_ICON, ":/info.svg")
U8_STRING_IMPL(LOGIN_ICON, ":/login.svg")

INT_IMPL(APP_WIDTH, 640)
INT_IMPL(APP_HEIGHT, 700)
INT_IMPL(ICON_SIZE, 30)
