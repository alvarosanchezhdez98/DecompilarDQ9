#include <m2c.h>

s32 func_ov031_0221e2e4(s32, s32, s32, s32, M2C_UNK *);
extern M2C_UNK data_ov031_0224e9a0;

#pragma thumb on
u8 func_ov031_0221e2bc(s32 arg0, s32 arg1) {
    return (u8) (func_ov031_0221e2e4(-1, arg0, arg1, 0, &data_ov031_0224e9a0) ^ -1);
}
#pragma thumb off
