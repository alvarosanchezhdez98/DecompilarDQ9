#include <m2c.h>
#pragma optimization_level 4

extern M2C_UNK data_ov001_02165880;

s32 func_ov001_0215ab20(s32 arg0) {
    if ((arg0 < 0) || (arg0 >= 0x18)) {
        return 0;
    }
    return (0x588 * arg0) + M2C_FIELD(&data_ov001_02165880, s32 *, 0x1C);
}
