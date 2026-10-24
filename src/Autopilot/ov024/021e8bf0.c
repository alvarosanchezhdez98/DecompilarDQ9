#include <m2c.h>


u32 func_ov024_021e8bf0(s32 arg0, void *arg1, s16 *arg2) {
    u32 temp_r0;
    u8 temp_r1;

    temp_r1 = M2C_FIELD(arg1, u8 *, 0x1C);
    if ((((u32) (temp_r1 << 0x1D) >> 0x1F) == 0) && (((u32) (temp_r1 << 0x1E) >> 0x1F) == 0) && (((u32) (temp_r1 << 0x1C) >> 0x1F) == 0) && (((u32) (temp_r1 << 0x1B) >> 0x1F) == 0) && (((u32) (temp_r1 << 0x1A) >> 0x1F) == 0)) {
        temp_r0 = (u32) (temp_r1 << 0x19) >> 0x1F;
        if (temp_r0 == 0) {
            return temp_r0;
        }
    }
    *arg2 = 0;
    return 0U;
}
