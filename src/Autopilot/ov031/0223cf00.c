#include <m2c.h>

M2C_UNK _Z24EnableSpecificInterruptsj(s32);
s32 _Z25DisableSpecificInterruptsj(M2C_UNK);
s32 _ZN13HPXEAllocator8AllocateEji(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020c9be0();
extern s32 data_ov031_02290d3c;

s32 ov13_02241240(M2C_UNK arg0, M2C_UNK arg1) {
    s32 temp_r0;
    s32 temp_r5;

    temp_r5 = _Z25DisableSpecificInterruptsj(1);
    temp_r0 = _ZN13HPXEAllocator8AllocateEji(data_ov031_02290d3c, arg0, arg1);
    if (temp_r0 == 0) {
        func_020c9be0();
    }
    _Z24EnableSpecificInterruptsj(temp_r5);
    return temp_r0;
}
