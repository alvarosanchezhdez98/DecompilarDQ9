#include <m2c.h>

extern M2C_UNK data_02107800;

s32 func_020421b0(s32 arg0) {
    return M2C_FIELD(&data_02107800, s32 *, 4) + (arg0 << 5);
}
