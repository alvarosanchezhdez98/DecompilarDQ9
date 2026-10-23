#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_0200fb8c();
s32 func_02012444(M2C_UNK *, M2C_UNK);
M2C_UNK func_02012a84(M2C_UNK *, s32 *, s32 *);
s32 func_02080d54(s32, s16, s16, s16);
s32 func_020e28dc(s32);
s32 func_020e2984(s32);
s32 func_ov017_021a4e70(s32);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;

s32 func_ov003_02160a68(void *arg0) {
    s32 sp4;
    s32 sp0;
    s32 temp_r6;
    s32 var_r4;

    var_r4 = 0;
    _ZN9GameState11GetInstanceEv();
    temp_r6 = func_0200fb8c();
    if ((func_02012444(&data_02114e30, 2) != 0) && (func_ov017_021a4e70(temp_r6) != 0)) {
        var_r4 = 1;
    }
    if (func_020e28dc(M2C_FIELD(arg0, s32 *, 0x390)) != 0) {
        if (func_020e2984(M2C_FIELD(arg0, s32 *, 0x390)) != 0) {
            var_r4 = 1;
        }
    } else if (M2C_FIELD(&data_02114e54, u8 *, 0x55) != 0) {
        func_02012a84(&data_02114e54, &sp4, &sp0);
        if (func_02080d54(M2C_FIELD(arg0, s32 *, 0x324), M2C_FIELD(arg0, s16 *, 0x488), (s16) sp4, (s16) sp0) == 0) {
            var_r4 = 1;
        }
    }
    return var_r4;
}
