#include <m2c.h>

void *func_0207f0ac(s32);
void *func_02081da8(s32, s16);

void func_02080c68(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_r0;
    void *temp_r0_2;

    temp_r0 = func_0207f0ac(arg0 + 0xC);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, u8 *, 0x12) = (u8) ((M2C_FIELD(temp_r0, u8 *, 0x12) & ~0xF) | (arg2 & 0xF));
    temp_r0_2 = func_02081da8(arg0, M2C_FIELD(temp_r0, s16 *, 8));
    if (temp_r0_2 != NULL) {
        M2C_FIELD(temp_r0_2, s16 *, 0xC2) = (s16) (((u32) (M2C_FIELD(temp_r0, u8 *, 0x12) << 0x1C) >> 0x1C) & 0xF);
    }
}
