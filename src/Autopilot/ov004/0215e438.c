#include <m2c.h>


s32 func_ov004_0215e438(void *arg0, u32 arg1) {
    s32 temp_r2;
    s32 var_r3;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0x40);
    var_r3 = 0;
    if ((temp_r2 != 0) && (arg1 < (u32) M2C_FIELD(arg0, u16 *, 0x4E))) {
        var_r3 = (arg1 * 0x28) + temp_r2;
    }
    return var_r3;
}
