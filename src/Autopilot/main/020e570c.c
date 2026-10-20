#include <m2c.h>

M2C_UNK func_020e5204();
M2C_UNK func_020e53bc(M2C_UNK, s32, M2C_UNK *, M2C_UNK (*)());

s32 func_020e56fc(M2C_UNK arg0, s32 arg1, s32 arg2) {
    M2C_UNK sp0;

    if ((arg1 != 0) && (arg2 != 0)) {
        func_020e53bc(arg0, arg1, &sp0, func_020e5204);
        return 1;
    }
    return 0;
}
