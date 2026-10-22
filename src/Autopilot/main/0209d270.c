#include <m2c.h>

s32 func_ov017_021d60f4(M2C_UNK);
s32 func_02094d6c();
s32 *func_02096134(s32, s32);

s32 func_0209d260(M2C_UNK arg0) {
    s32 *temp_r0_2;
    s32 temp_r0;

    temp_r0 = func_02094d6c();
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r0_2 = func_02096134(temp_r0, func_ov017_021d60f4(arg0));
    if (temp_r0_2 == NULL) {
        return 0;
    }
    *temp_r0_2 |= 0x4000;
    return 1;
}
