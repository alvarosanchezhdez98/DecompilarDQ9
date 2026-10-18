#include <m2c.h>

s32 func_0209ca2c(M2C_UNK *);
M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);
extern M2C_UNK data_02109bf4;

s32 func_ov001_0216376c(M2C_UNK arg0) {
    if (func_0209ca2c(&data_02109bf4) != 0) {
        func_ov017_021d6134(arg0, 1);
    } else {
        func_ov017_021d6134(arg0, 0);
    }
    return 1;
}
