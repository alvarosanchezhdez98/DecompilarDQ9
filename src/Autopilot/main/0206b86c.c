#include <m2c.h>

s32 func_02042648(M2C_UNK);
M2C_UNK func_020696bc(M2C_UNK, s32 *, M2C_UNK);

s32 func_0206b85c(M2C_UNK arg0, s32 *arg1, M2C_UNK arg2) {
    s32 sp0;

    func_020696bc(arg0, &sp0, 1);
    *arg1 = sp0 - (func_02042648(arg2) + 1);
    return 0;
}
