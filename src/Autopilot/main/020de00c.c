#include <m2c.h>


void func_020ddffc(void *arg0) {
    s32 temp_r1;

    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) + M2C_FIELD(arg0, s32 *, 0x20));
    temp_r1 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r1 < 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_r1 + 1);
    }
    if ((s32) M2C_FIELD(arg0, s32 *, 0x18) >= 0x1000) {
        M2C_FIELD(arg0, s32 *, 0x18) = 0x1000;
        M2C_FIELD(arg0, s8 *, 4) = 3;
    }
}
