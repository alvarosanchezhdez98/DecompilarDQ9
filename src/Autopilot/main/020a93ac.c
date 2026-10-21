#include <m2c.h>


s32 func_020a939c(void *arg0, s32 arg1) {
    s32 temp_r0;

    if ((arg1 < 0) || (arg1 >= (s32) ((u32) (M2C_FIELD(arg0, s32 *, 0) << 0x14) >> 0x14)) || (temp_r0 = M2C_FIELD(arg0, s32 *, 4), (temp_r0 == 0))) {
        return 0;
    }
    return temp_r0 + (arg1 << 6);
}
