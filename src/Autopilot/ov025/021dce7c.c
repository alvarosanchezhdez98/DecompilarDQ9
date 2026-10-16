#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_0202ea10(s32, s32, M2C_UNK);
M2C_UNK func_ov000_02167f10(s32);
M2C_UNK func_ov000_0216dbf0(s32, s32 *, M2C_UNK, M2C_UNK);
M2C_UNK func_ov025_021def64(s32, u16 *, M2C_UNK);

s32 func_ov025_021dce7c(s32 arg0, u16 *arg1, s32 arg2) {
    s32 sp0;
    u16 temp_r1;

    if (arg1 != NULL) {
        _ZN9GameState11GetInstanceEv();
        temp_r1 = *arg1;
        if ((temp_r1 != 0x30D) && (temp_r1 != 0x246)) {
            goto block_5;
        }
        sp0 = arg2;
        func_ov000_02167f10(arg0);
        func_ov025_021def64(arg0, arg1, 0x18);
        func_ov000_0216dbf0(arg0 + 0xC18, &sp0, 1, 1);
        func_0202ea10(arg0 + 0xC18, 0x199, 0x7D0);
        return 1;
    }
block_5:
    return 0;
}
