#include <m2c.h>

extern M2C_UNK data_ov031_0224e6e0;

#pragma thumb on
s32 func_ov031_0221d06c(void) {
    return M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x10);
}
#pragma thumb off
