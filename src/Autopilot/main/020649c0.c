#include <m2c.h>

void *func_02064490();
s32 func_02064530(M2C_UNK, s32, void *);

s32 func_020649b0(M2C_UNK arg0, s32 arg1, void *arg2) {
    void *temp_r0;

    temp_r0 = func_02064490();
    if (temp_r0 == NULL) {
        return 0;
    }
    M2C_FIELD(arg2, s32 *, 0x30) = 0;
    if (func_02064530(arg0, M2C_FIELD(temp_r0, s32 *, 0xC), arg2) != 0) {
        return 1;
    }
    return 0;
}
