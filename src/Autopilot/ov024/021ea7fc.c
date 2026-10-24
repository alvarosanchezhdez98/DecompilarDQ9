#include <m2c.h>


s32 func_ov024_021ea7fc(s32 arg0, void *arg1, s32 arg2) {
    u32 temp_r0;

    if (arg2 == 0) {
        return 0;
    }
    if ((((u32) (M2C_FIELD(arg1, s32 *, 8) * 4) >> 0x1F) != 0) && (((u32) (M2C_FIELD(arg1, s32 *, 4) << 0x14) >> 0x14) != 0x1F9)) {
        return 0;
    }
    temp_r0 = (u32) (M2C_FIELD(arg1, s32 *, 4) << 0x14) >> 0x14;
    if (temp_r0 == 0x70) {
        return 0;
    }
    if (temp_r0 != 0x48) {
        return 1;
    }
    return 0;
}
