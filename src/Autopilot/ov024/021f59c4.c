#include <m2c.h>

void *func_ov000_021536f8(s32);

s32 func_ov024_021f59c4(s32 *arg0, s16 arg1, s32 arg2, s32 *arg3, s16 *arg4) {
    void *temp_r0;

    temp_r0 = func_ov000_021536f8(*arg0);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), u16 *, 2) != 0) {
        return 0;
    }
    *arg3 = 1;
    *arg4 = arg1;
    return 1;
}
