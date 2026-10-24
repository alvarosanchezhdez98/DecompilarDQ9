#include <m2c.h>

void *func_ov000_02160094(M2C_UNK, M2C_UNK);
s32 func_ov017_0218b5b0();
s32 func_ov017_02191b58(s32, u16);
M2C_UNK func_ov017_0219230c(s32, u16, M2C_UNK);
M2C_UNK func_ov017_02192400(s32, u16);

s32 func_ov025_021e8670(s32 arg0, M2C_UNK arg1) {
    s32 temp_r4;
    s32 var_r0;
    u16 temp_r5;

    temp_r4 = func_ov017_0218b5b0();
    temp_r5 = M2C_FIELD(func_ov000_02160094(arg1, 0), u16 *, 0x20);
    if (((s32) temp_r5 >= 0) && ((s32) temp_r5 <= 3)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if ((var_r0 != 0) && (func_ov017_02191b58(temp_r4, temp_r5) & 2)) {
        func_ov017_0219230c(temp_r4, temp_r5, 8);
        return 1;
    }
    func_ov017_02192400(temp_r4, temp_r5);
    return 1;
}
