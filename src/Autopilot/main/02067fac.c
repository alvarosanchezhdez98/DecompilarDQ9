#include <m2c.h>

void *func_0204254c(s32, M2C_UNK);

s32 func_02067f9c(void *arg0, s32 arg1, M2C_UNK arg2) {
    void *temp_r0;

    if ((arg0 != NULL) && (((u32) (M2C_FIELD(arg0, s32 *, 8) * 8) >> 0x1F) != 0)) {
        return 1;
    }
    if (arg1 == 0) {
        return 0;
    }
    temp_r0 = func_0204254c(arg1, arg2);
    if (temp_r0 != NULL) {
        return (s32) (M2C_FIELD(temp_r0, s8 *, 5) << 0x19) >> 0x1F;
    }
    return 0;
}
