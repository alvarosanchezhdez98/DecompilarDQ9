#include <m2c.h>


s32 func_02048418(void *arg0, s32 arg1) {
    s32 *temp_r3;
    s32 temp_r2;

    temp_r3 = M2C_FIELD(arg0, s32 **, 0x130);
    temp_r2 = *temp_r3;
    if (!(arg1 & temp_r2)) {
        return 0;
    }
    *temp_r3 = (s32) (u16) (temp_r2 & ~arg1);
    return 1;
}
