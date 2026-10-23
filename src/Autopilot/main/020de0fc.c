#include <m2c.h>

s32 rand();

void func_020de0ec(void *arg0) {
    s32 temp_r1;
    u8 temp_r0;

    temp_r1 = rand() % 10000;
    M2C_FIELD(arg0, u8 *, 0x24) = 0U;
    if (temp_r1 < 0x19) {
        M2C_FIELD(arg0, u8 *, 0x24) = (u8) (M2C_FIELD(arg0, u8 *, 0x24) | 4);
        return;
    }
    temp_r0 = M2C_FIELD(arg0, u8 *, 0x24);
    if (temp_r1 < 0xC8) {
        M2C_FIELD(arg0, u8 *, 0x24) = (u8) (temp_r0 | 2);
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x24) = (u8) (temp_r0 | 1);
}
