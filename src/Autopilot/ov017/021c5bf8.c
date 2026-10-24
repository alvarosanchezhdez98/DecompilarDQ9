#include <m2c.h>

s32 func_0207d78c();
s32 func_0207d978(s32, u16);
s32 func_0207d9bc(s32, u16);

s32 func_ov017_021c5bf8(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;

    if (arg0 < 4) {
        temp_r0 = func_0207d78c();
        if (func_0207d978(temp_r0, arg1) != 0) {
            temp_r0_2 = func_0207d9bc(temp_r0, arg1);
            if ((temp_r0_2 != 0) && (M2C_FIELD((temp_r0_2 + arg0), s8 *, 8) != -1)) {
                return 1;
            }
        }
    }
    return 0;
}
