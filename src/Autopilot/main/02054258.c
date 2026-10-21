#include <m2c.h>


void func_02054248(void *arg0) {
    s32 temp_r1;
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0x18C);
    if (!(temp_r2 & 0x100)) {
        return;
    }
    temp_r1 = temp_r2 & 0x80;
    if (temp_r1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x18C) = (s32) (temp_r2 | 1);
    } else if (temp_r1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x18C) = (s32) (temp_r2 & ~1);
    }
    M2C_FIELD(arg0, s32 *, 0x18C) = (s32) (M2C_FIELD(arg0, s32 *, 0x18C) & ~0x100);
}
