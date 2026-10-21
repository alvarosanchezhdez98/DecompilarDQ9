#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
M2C_UNK func_02056d10();

s32 func_020556dc(s32 *arg0, s32 arg1) {
    s32 temp_r0;

    if (arg1 == 0) {
        return 0;
    }
    temp_r0 = _ZN13SafeAllocator8AllocateEj(arg1, 0x170);
    *arg0 = temp_r0;
    if (temp_r0 == 0) {
        return 0;
    }
    func_02056d10();
    return 1;
}
