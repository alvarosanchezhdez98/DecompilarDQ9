#include <m2c.h>

void *func_020421a0();
M2C_UNK func_0205d304(s32, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK func_ov000_02177d04(s32, s32);
M2C_UNK func_ov000_0217c638(s32, M2C_UNK, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov000_02177bf0(s32 arg0, void *arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r6;
    void *temp_r3;

    if (arg1 != NULL) {
        temp_r5 = M2C_FIELD(arg1, s32 *, 0x44);
        temp_r6 = M2C_FIELD(arg1, s32 *, 0x48);
        func_ov000_0217c638(arg0, arg2, arg3);
        temp_r3 = arg0 + 0x188;
        M2C_FIELD(temp_r3, s16 *, 0xA0) = 0x15;
        M2C_FIELD(temp_r3, s16 *, 0xA2) = 7;
        M2C_FIELD(temp_r3, s16 *, 0xA4) = (s16) ((temp_r5 >> 3) + 9);
        M2C_FIELD(temp_r3, s16 *, 0xA6) = (s16) ((temp_r6 >> 3) + 1);
        M2C_FIELD(temp_r3, s16 *, 0xA8) = 0xC;
        M2C_FIELD(temp_r3, s16 *, 0xAA) = 5;
        M2C_FIELD(temp_r3, s16 *, 0xAC) = 0xA;
        M2C_FIELD(temp_r3, s16 *, 0xAE) = 0xC;
        M2C_FIELD(temp_r3, s8 *, 0xB1) = 5;
        temp_r5_2 = M2C_FIELD(func_020421a0(), s32 *, 0x5C);
        memset(temp_r5_2, 0, 0x960);
        func_ov000_02177d04(arg0, temp_r5_2);
        func_0205d304(arg0 + 0x188, temp_r5_2, 0, 0, 0, 1, 0, 0);
    }
}
