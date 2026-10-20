#include <m2c.h>

M2C_UNK func_020dfbdc();
M2C_UNK func_020e0280(M2C_UNK, s32, M2C_UNK *, M2C_UNK (*)());

s32 func_020e038c(M2C_UNK arg0, s32 arg1, s32 arg2) {
    M2C_UNK sp0;

    if ((arg1 != 0) && (arg2 != 0)) {
        func_020e0280(arg0, arg1, &sp0, func_020dfbdc);
        return 1;
    }
    return 0;
}
