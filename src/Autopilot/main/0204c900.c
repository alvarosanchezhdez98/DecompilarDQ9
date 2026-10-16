#include <m2c.h>

M2C_UNK func_0204b878(s32, void *, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);

void func_0204c8f0(void *arg0) {
    s32 temp_r0;
    u8 temp_r2;

    temp_r0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_r0 != 0) {
        temp_r2 = M2C_FIELD(arg0, u8 *, 0xC5);
        if ((temp_r2 & 1) && (M2C_FIELD(arg0, s32 *, 0x9C) != 0)) {
            if (!(temp_r2 & 0x20)) {
                func_0204b878(temp_r0, arg0 + 0xC8, 0, 0, (s32) M2C_FIELD(arg0, s16 *, 0xAC), (s32) M2C_FIELD(arg0, s16 *, 0xAE), (s32) M2C_FIELD(arg0, s16 *, 0xC8), (s32) M2C_FIELD(arg0, s16 *, 0xC0), (s32) M2C_FIELD(arg0, u16 *, 0xC2));
            }
        }
    }
}
