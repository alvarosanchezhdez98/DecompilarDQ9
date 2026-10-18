#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState18SetDayTimerRunningEi(s32, M2C_UNK);
s32 func_ov017_021d60f4();

s32 func_ov001_02164080(void) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r4 = func_ov017_021d60f4();
    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (temp_r4 != 0) {
        _ZN9GameState18SetDayTimerRunningEi(temp_r0, 0);
    } else {
        _ZN9GameState18SetDayTimerRunningEi(temp_r0, 1);
    }
    return 1;
}
