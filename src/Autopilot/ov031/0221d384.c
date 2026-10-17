#include <m2c.h>

s32 func_ov031_0221ecb4();
extern M2C_UNK data_ov031_0224b070;

#pragma thumb on
s32 func_ov031_0221d384(s32 arg0) {
    if (arg0 == -1) {
        M2C_FIELD(&data_ov031_0224b070, s32 *, 4) = arg0;
        return 0;
    }
    if (M2C_FIELD(&data_ov031_0224b070, s32 *, 4) != arg0) {
        M2C_FIELD(&data_ov031_0224b070, s32 *, 4) = arg0;
        return func_ov031_0221ecb4();
    }
    return 0;
}
#pragma thumb off
