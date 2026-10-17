#include <m2c.h>


void func_ov000_02180b50(void *arg0) {
    s32 temp_r1;
    s32 temp_r1_2;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x934);
    if (temp_r1 == 0) {
        M2C_FIELD(arg0, s32 *, 0x930) = 0x180;
        M2C_FIELD(arg0, s32 *, 0x938) = 0;
        M2C_FIELD(arg0, s32 *, 0x934) = 1;
        return;
    }
    if (temp_r1 != 1) {
        return;
    }
    temp_r1_2 = M2C_FIELD(arg0, s32 *, 0x930) - (M2C_FIELD(arg0, s32 *, 0x94C) * 3);
    M2C_FIELD(arg0, s32 *, 0x930) = temp_r1_2;
    if (temp_r1_2 <= 0x80) {
        M2C_FIELD(arg0, s32 *, 0x930) = 0x80;
        M2C_FIELD(arg0, s32 *, 0x934) = -1;
    }
}
