#include <m2c.h>

s32 func_ov031_0221d450(s32, void *, s32 *, s32);
s32 func_ov031_0221d52c(s32, void *, s32 *, s32);
s32 func_ov031_0221d604(s32, void *, s32 *, s32);
s32 func_ov031_0221d6a8(void *);
u32 func_ov031_0221e638(u16);

#pragma thumb on
s32 func_ov031_0221d3b0(s32 arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 sp0;
    s32 var_r5;
    u32 temp_r0;
    void *temp_r7;

    var_r5 = arg0;
    sp0 = arg3;
    temp_r7 = arg1 + 0xC;
    if (func_ov031_0221e638(M2C_FIELD(arg1, u16 *, 0xC)) < 1U) {
        *arg2 += 1;
        return var_r5;
    }
    if (M2C_FIELD(temp_r7, u8 *, 0xF) != 0x11) {
        *arg2 += 1;
        return var_r5;
    }
    if (func_ov031_0221d6a8(arg1 + 0xC) > 0) {
        *arg2 += 1;
        return var_r5;
    }
    temp_r0 = func_ov031_0221e638(M2C_FIELD(temp_r7, u16 *, 6));
    switch (temp_r0) {                              /* irregular */
    case 0x1010:
        var_r5 = func_ov031_0221d450(var_r5, arg1, arg2, sp0);
        break;
    case 0x2010:
        var_r5 = func_ov031_0221d52c(var_r5, arg1, arg2, sp0);
        break;
    case 0x3010:
        var_r5 = func_ov031_0221d604(var_r5, arg1, arg2, sp0);
        break;
    }
    return var_r5;
}
#pragma thumb off
