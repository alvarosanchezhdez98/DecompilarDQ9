#include <m2c.h>

extern M2C_UNK data_02107800;

s32 func_020421a0(void) {
    return M2C_FIELD(&data_02107800, s32 *, 0x1C);
}
