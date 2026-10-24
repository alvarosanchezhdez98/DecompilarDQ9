#include <m2c.h>
#pragma optimization_level 4

void *func_020421a0();
s32 func_0205bafc(void *);
M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
void *func_0205d81c(void *, M2C_UNK);
M2C_UNK func_ov000_02176210(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov000_02178d28();
M2C_UNK func_ov000_02178f28(s32, void *, s32);
M2C_UNK func_ov000_0217ab8c(void *, M2C_UNK, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov000_02178ba8(s32 arg0, void *arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_r4;
    s32 temp_r8;
    u32 temp_r8_2;
    s32 var_r4;
    void *temp_r0;
    void *temp_r5;

    func_ov000_02178d28();
    temp_r8 = M2C_FIELD(arg1, s32 *, 0x44);
    temp_r4 = M2C_FIELD(arg1, s32 *, 0x48);
    func_ov000_0217ab8c(arg1, arg2, arg3);
    temp_r5 = arg0 + 0x188;
    M2C_FIELD(temp_r5, s16 *, 0xA0) = 0x10;
    M2C_FIELD(temp_r5, s16 *, 0xA2) = 9;
    M2C_FIELD(temp_r5, s16 *, 0xA4) = (s16) ((temp_r8 >> 3) + 0x10);
    M2C_FIELD(temp_r5, s16 *, 0xA6) = (s16) (temp_r4 >> 3);
    M2C_FIELD(temp_r5, s16 *, 0xA8) = 0xC;
    M2C_FIELD(temp_r5, s16 *, 0xAA) = 8;
    M2C_FIELD(temp_r5, s16 *, 0xAC) = 0xA;
    M2C_FIELD(temp_r5, s16 *, 0xAE) = 0xC;
    M2C_FIELD(temp_r5, s8 *, 0xB1) = 0xF;
    var_r4 = 0;
    if (func_0205bafc(temp_r5 + 0x54) > 4) {
        var_r4 = 1;
    }
    temp_r8_2 = M2C_FIELD(func_020421a0(), s32 *, 0x5C);
    memset(temp_r8_2, 0, 0x960);
    func_ov000_02178f28(arg0, arg1, temp_r8_2);
    func_0205d304(temp_r5, temp_r8_2, 0, 0, var_r4, 1, 0, 0);
    temp_r0 = func_0205d81c(temp_r5, 0x22);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s16 *, 0xC2) = 0;
    }
    func_ov000_02176210(arg0 + 0x188, 0xF, 0x22);
}
