#include <m2c.h>

M2C_UNK VectorizedMemset(M2C_UNK, M2C_UNK, s32);
s32 func_ov031_02211aec();
s32 func_ov031_0223f264(M2C_UNK, M2C_UNK, s32);

s32 ov00_021ED3AC(M2C_UNK arg0, M2C_UNK arg1, s32 arg2) {
    if (func_ov031_02211aec() != 0) {
        return 0;
    }
    VectorizedMemset(arg0, 0, arg2 * 0xB0);
    return func_ov031_0223f264(arg0, arg1, arg2);
}
