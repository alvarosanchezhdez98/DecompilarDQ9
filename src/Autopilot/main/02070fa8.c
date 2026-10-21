#include <m2c.h>


s32 func_02070f98(void *arg0, s32 arg1) {
    s32 temp_r2;

    if ((arg1 < 0) || (arg1 >= (s32) ((u32) (M2C_FIELD(arg0, s32 *, 0) << 0x14) >> 0x14)) || (temp_r2 = M2C_FIELD(arg0, s32 *, 4), (temp_r2 == 0))) {
        return 0;
    }
    return (arg1 * 0x84) + temp_r2;
}
