#include <m2c.h>

M2C_UNK func_020556cc(s32, s32, s32, s32);
s32 func_020556dc(void *, s32);
M2C_UNK func_02056d80(s32);

s32 func_02055660(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 == 0) {
        return 0;
    }
    if (arg2 == 0) {
        return 0;
    }
    if (arg3 == 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 0) = arg3;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    if (func_020556dc(arg0 + 4, M2C_FIELD(arg0, s32 *, 0)) != 0) {
        func_020556cc(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 0));
        func_02056d80(M2C_FIELD(arg0, s32 *, 4));
    }
    return 1;
}
