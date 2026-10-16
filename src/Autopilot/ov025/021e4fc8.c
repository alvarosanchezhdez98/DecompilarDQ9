#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_0200fd48(s32, s32);
s32 func_02057924();
s32 func_02058658(s32, s32);
M2C_UNK func_02059cc8();
s32 *func_ov025_021e8cf0(s32, u8);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e4fc8(void *arg0) {
    s32 *temp_r0;

    temp_r0 = func_ov025_021e8cf0(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC), M2C_FIELD(arg0, u8 *, 8));
    if (temp_r0 != NULL) {
        func_0200fd48(_ZN9GameState11GetInstanceEv(), *temp_r0);
        if (func_02058658(func_02057924(), *temp_r0) != 0) {
            func_02059cc8();
        }
    }
    return 1;
}
