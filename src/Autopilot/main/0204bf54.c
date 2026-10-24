#include <m2c.h>


void func_0204bf44(void *arg0, s32 arg1, void *arg2) {
    u32 temp_r3_2;
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r1_3;
    void *temp_r1_4;
    void *temp_r1_5;
    void *temp_r1_6;
    void *temp_r1_7;
    void *temp_r3;

    M2C_FIELD(arg0, void **, 0) = arg2;
    M2C_FIELD(arg0, void **, 4) = (void *) (arg2 + M2C_FIELD(arg2, s32 *, 0x24));
    M2C_FIELD(arg0, void **, 8) = (void *) (arg2 + M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x28));
    M2C_FIELD(arg0, void **, 0xC) = (void *) (arg2 + M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x2C));
    M2C_FIELD(arg0, void **, 0x10) = (void *) (arg2 + M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x30));
    temp_r3 = M2C_FIELD(arg0, void **, 0);
    if (M2C_FIELD(temp_r3, s32 *, 0) == 3) {
        M2C_FIELD(arg0, void **, 0x14) = (void *) (arg2 + M2C_FIELD(temp_r3, s32 *, 0x38));
    }
    temp_r1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(temp_r1, s16 *, 8) << M2C_FIELD(temp_r1, s32 *, 4));
    temp_r1_2 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(temp_r1_2, s16 *, 0xA) << M2C_FIELD(temp_r1_2, s32 *, 4));
    temp_r1_3 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(temp_r1_3, s16 *, 0xC) << M2C_FIELD(temp_r1_3, s32 *, 4));
    temp_r1_4 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(temp_r1_4, s16 *, 0xE) << M2C_FIELD(temp_r1_4, s32 *, 4));
    temp_r1_5 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_r1_5, s16 *, 0x10) << M2C_FIELD(temp_r1_5, s32 *, 4));
    temp_r1_6 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r1_6, s16 *, 0x12) << M2C_FIELD(temp_r1_6, s32 *, 4));
    temp_r1_7 = M2C_FIELD(arg0, void **, 0);
    temp_r3_2 = M2C_FIELD(temp_r1_7, u32 *, 0x20);
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) ((M2C_FIELD(temp_r1_7, s32 *, 0x1C) * temp_r3_2) + (temp_r3_2 >> 1));
}
