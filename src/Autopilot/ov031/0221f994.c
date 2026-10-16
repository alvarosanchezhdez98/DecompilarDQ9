#include <m2c.h>

extern M2C_UNK data_ov031_0224f670;

#pragma thumb on
s32 func_ov031_0221f994(void) {
    return M2C_FIELD(&data_ov031_0224f670, s32 *, 0x2C);
}
#pragma thumb off
