#include <m2c.h>

s32 func_ov031_02207380(M2C_UNK, M2C_UNK, M2C_UNK, s32);

s32 func_ov031_022414cc(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    s32 temp_r0;

    temp_r0 = func_ov031_02207380(arg1, arg2, arg3, arg4);
    if (temp_r0 >= 0) {
        return temp_r0;
    }
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        return -0x3EA;
    }
    if (temp_r0 == -0x38) {
        return 0;
    }
    return -0x3E9;
}
