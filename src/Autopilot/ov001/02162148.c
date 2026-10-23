#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState12SetTimeOfDayE9TimeOfDay(s32, s32);
s32 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_02162148(M2C_UNK arg0) {
    s32 temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    _ZN9GameState12SetTimeOfDayE9TimeOfDay(temp_r4, func_ov017_021d60f4(arg0));
    return 1;
}
