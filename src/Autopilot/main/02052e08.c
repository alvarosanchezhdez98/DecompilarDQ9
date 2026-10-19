#include <m2c.h>


s16 func_02052df8(void *arg0, s32 arg1) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x150);
    if (temp_r0 != 0) {
        return M2C_FIELD((temp_r0 + (arg1 * 2)), s16 *, 0x488);
    }
    return -1;
}
