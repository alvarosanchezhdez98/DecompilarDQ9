#include <m2c.h>

extern M2C_UNK data_ov031_0224e6e0;

#pragma thumb on
void func_ov031_0221d060(s32 arg0) {
    M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0x10) = arg0;
}
#pragma thumb off
