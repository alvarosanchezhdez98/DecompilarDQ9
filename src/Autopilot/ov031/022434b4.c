#include <m2c.h>

s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov031_02291e3c;

s32 func_ov031_022434b4(s32 arg0, M2C_UNK arg1) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = _Z20DisableIRQInterruptsv();
    temp_r4 = _ZN13SafeAllocator8AllocateEj(&data_ov031_02291e3c, arg1);
    _Z20SetIRQInterruptStatei(temp_r5);
    return temp_r4;
}
