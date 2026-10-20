#include <m2c.h>

u8 FastIntModulus(s32, u16);
M2C_UNK _Z24EnableSpecificInterruptsj(s32);
s32 _Z25DisableSpecificInterruptsj(M2C_UNK);
M2C_UNK func_020c9be0();

void ov13_02240288(void *arg0, s32 arg1) {
    s32 temp_r6;
    u8 temp_r0;

    temp_r6 = _Z25DisableSpecificInterruptsj(1);
    temp_r0 = FastIntModulus(M2C_FIELD(arg0, u8 *, 3) + 1, M2C_FIELD(arg0, u16 *, 0));
    if (temp_r0 == M2C_FIELD(arg0, u8 *, 2)) {
        func_020c9be0();
    }
    M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 3) * 4)), s32 *, 4) = arg1;
    M2C_FIELD(arg0, u8 *, 3) = temp_r0;
    _Z24EnableSpecificInterruptsj(temp_r6);
}
