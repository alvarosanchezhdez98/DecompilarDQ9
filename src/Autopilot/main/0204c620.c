#include <m2c.h>


void func_0204c610(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3, s16 *arg4, s16 *arg5) {
    void *temp_lr;

    if (arg1 < 0) {
        return;
    }
    if (arg1 >= 0x12) {
        return;
    }
    temp_lr = arg0 + (arg1 * 2);
    *arg2 = M2C_FIELD(temp_lr, s16 *, 0xC);
    *arg3 = M2C_FIELD(temp_lr, s16 *, 0x30);
    *arg4 = M2C_FIELD(temp_lr, s16 *, 0x54);
    *arg5 = M2C_FIELD(temp_lr, s16 *, 0x78);
}
