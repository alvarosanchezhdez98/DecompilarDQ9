#include <m2c.h>

M2C_UNK _Z24EnableSpecificInterruptsj(s32);
s32 _Z25DisableSpecificInterruptsj(M2C_UNK);
M2C_UNK _ZN13HPXEAllocator4FreeEPv(s32);
extern s32 data_ov031_02290d3c;

void ov13_022412B0(s32 *arg0) {
    s32 temp_r4;

    temp_r4 = _Z25DisableSpecificInterruptsj(1);
    if (*arg0 == 0) {
        return;
    }
    _ZN13HPXEAllocator4FreeEPv(data_ov031_02290d3c);
    _Z24EnableSpecificInterruptsj(temp_r4);
    *arg0 = 0;
}
