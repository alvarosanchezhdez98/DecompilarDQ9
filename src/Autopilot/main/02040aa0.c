#include <m2c.h>

s32 func_0203ce00(s32);
s32 func_020415c4(s32);
s32 func_02041654();

s32 func_02040a90(void *arg0) {
    s32 temp_r1;
    s32 temp_r1_2;

    temp_r1_2 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r1_2 != 0) {
        return func_0203ce00(temp_r1_2);
    }
    temp_r1 = M2C_FIELD(arg0, s32 *, 0x18);
    if (temp_r1 != 0) {
        return func_020415c4(temp_r1);
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C) == 0) {
        return 0;
    }
    return func_02041654();
}
