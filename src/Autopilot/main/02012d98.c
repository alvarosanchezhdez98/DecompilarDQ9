#include <m2c.h>

s32 _ZN14AllocatorUnion8AllocateEj(M2C_UNK, s32);

s32 func_02012d88(M2C_UNK arg0, s32 arg1) {
    s32 var_r0;

    var_r0 = _ZN14AllocatorUnion8AllocateEj(arg0, (arg1 + 3) & ~3);
    if (var_r0 == 0) {
        var_r0 = 0;
    }
    return var_r0;
}
