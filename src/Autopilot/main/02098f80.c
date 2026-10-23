#include <m2c.h>

s32 func_020421a0();
M2C_UNK func_02046608(s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK memcpy(s32, M2C_UNK, s32);
s32 strlen(s32);

void func_02098f70(s32 *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    s32 temp_r5;

    temp_r5 = func_020421a0();
    memcpy(*arg0, arg2, arg3);
    *arg0 += arg3;
    func_02046608(temp_r5, 0xC, arg1, *arg0, 0xE3, 0, 1);
    *arg0 += strlen(*arg0);
}
