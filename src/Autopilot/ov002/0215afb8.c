#include <m2c.h>

s32 func_0204c7e0();
M2C_UNK func_0205a330(s32, s32);
M2C_UNK func_0205a370(s32, M2C_UNK);
void *func_0205a3d0(s32, M2C_UNK);
M2C_UNK func_0205ae8c(s32);
void *func_0205d8c4(void *);
M2C_UNK func_020e27ec(s32, M2C_UNK, s16, s16);
s32 func_020e28dc();

void func_ov002_0215afb8(void *arg0) {
    s16 temp_r4;
    s16 temp_r5;
    s32 temp_r6;
    void *temp_r0;
    void *temp_r0_2;

    if (!(M2C_FIELD(arg0, s32 *, 0x247C) & 4)) {
        return;
    }
    temp_r0 = func_0205d8c4(arg0 + 0xEC8);
    if (temp_r0 == NULL) {
        return;
    }
    if ((func_0204c7e0() != 0) && (M2C_FIELD(arg0, s32 *, 4) != 0)) {
        if (func_020e28dc() != 0) {
            return;
        }
        temp_r6 = M2C_FIELD(arg0, s32 *, 0x1A6C);
        temp_r4 = M2C_FIELD(temp_r0, s16 *, 0xBC) + (s16) (M2C_FIELD(temp_r0, s16 *, 0xAC) * 8);
        temp_r5 = M2C_FIELD(temp_r0, s16 *, 0xBE) + (s16) (M2C_FIELD(temp_r0, s16 *, 0xAE) * 8);
        func_0205a370(temp_r6, 0);
        temp_r0_2 = func_0205a3d0(temp_r6, 0);
        if (temp_r0_2 != NULL) {
            M2C_FIELD(temp_r0_2, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0_2, u8 *, 0x15) | 8);
        }
        func_0205a330(temp_r6, M2C_FIELD(arg0, s32 *, 0x1BA0));
        func_020e27ec(temp_r6, 0, (s16) (temp_r4 - 8), (s16) (temp_r5 - 2));
        func_0205ae8c(M2C_FIELD(arg0, s32 *, 0x1A68));
    }
}
