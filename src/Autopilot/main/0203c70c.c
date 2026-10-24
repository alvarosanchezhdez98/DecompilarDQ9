#include <m2c.h>


void func_0203c6fc(void *arg0, s16 arg1) {
    u8 temp_r1;
    s32 temp_r1_2;
    void *temp_r2;

    if (arg1 < 0) {
        return;
    }
    temp_r2 = arg0 + 4 + (arg1 * 0x28);
    temp_r1 = M2C_FIELD(temp_r2, u8 *, 0x24);
    if (temp_r1 == 0) {
        return;
    }
    temp_r1_2 = temp_r1 - 1;
    M2C_FIELD(temp_r2, u8 *, 0x24) = temp_r1_2;
    if (!(temp_r1_2 & 0xFF)) {
        M2C_FIELD(arg0, u16 *, 0x512) = (u16) (M2C_FIELD(arg0, u16 *, 0x512) - 1);
    }
}
