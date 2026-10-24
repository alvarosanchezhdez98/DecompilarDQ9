#include <m2c.h>

void *func_ov000_021536f8(s32);

s32 func_ov024_021f6230(s32 *arg0, s16 arg1, s32 arg2, s32 *arg3, s16 *arg4) {
    void *temp_r0;
    void *temp_r2;

    temp_r0 = func_ov000_021536f8(*arg0);
    if (temp_r0 == NULL) {
        return 0;
    }
    temp_r2 = M2C_FIELD(temp_r0, void **, 0x138);
    if (((u32) M2C_FIELD(temp_r2, u16 *, 8) >= 0xFFFFU) || ((s32) ((s32) (M2C_FIELD(temp_r2, s32 *, 0x58) << 0x1D) >> 0x1D) >= 2)) {
        return 0;
    }
    *arg3 = 1;
    *arg4 = arg1;
    return 1;
}
