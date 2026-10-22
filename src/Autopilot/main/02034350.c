#include <m2c.h>

s32 func_0202ae18();
s32 func_0202b7d8(s32);
void *func_0202c178(s32, s16);
M2C_UNK func_ov017_0218b5b0();

s32 func_02034340(void *arg0) {
    s32 temp_r4;
    s32 var_r5;

    temp_r4 = func_0202ae18();
    func_ov017_0218b5b0();
    var_r5 = 0;
    if ((func_0202b7d8(temp_r4) != 0) && (func_0202c178(temp_r4, M2C_FIELD(arg0, s16 *, 4)) != NULL) && (((u32) (M2C_FIELD(func_0202c178(temp_r4, M2C_FIELD(arg0, s16 *, 4)), u16 *, 2) << 0x11) >> 0x1F) != 0)) {
        var_r5 = 1;
    }
    return var_r5;
}
