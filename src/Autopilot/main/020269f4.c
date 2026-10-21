#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32, s32);

void func_020269e4(void *arg0, s32 arg1) {
    u8 temp_ip;

    temp_ip = M2C_FIELD(arg0, u8 *, 0x780);
    if ((u32) temp_ip >= 0x14U) {
        return;
    }
    if (arg1 == 0) {
        return;
    }
    VectorizedInvertedMemcpy(arg1, (temp_ip * 0x1C) + (s32) (arg0 + 0x784));
    M2C_FIELD(arg0, u8 *, 0x780) = (u8) (M2C_FIELD(arg0, u8 *, 0x780) + 1);
}
