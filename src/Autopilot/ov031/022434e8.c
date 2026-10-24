#include <m2c.h>

s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
M2C_UNK _ZN13SafeAllocator4FreeEPv(M2C_UNK *, s32);
extern M2C_UNK data_ov031_02291e3c;

void func_ov031_022434e8(s32 arg0, s32 arg1) {
    s32 temp_r4;

    if (arg1 == 0) {
        return;
    }
    temp_r4 = _Z20DisableIRQInterruptsv();
    _ZN13SafeAllocator4FreeEPv(&data_ov031_02291e3c, arg1);
    _Z20SetIRQInterruptStatei(temp_r4);
}
