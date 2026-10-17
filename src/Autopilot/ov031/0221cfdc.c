#include <m2c.h>

M2C_UNK func_ov031_0221c4ac();
extern M2C_UNK data_ov031_0224e6e0;

#pragma thumb on
void func_ov031_0221cfdc(void) {
    if (M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0xC) != 0) {
        func_ov031_0221c4ac();
        M2C_FIELD(&data_ov031_0224e6e0, s32 *, 0xC) = 0;
    }
    if (M2C_FIELD(&data_ov031_0224e6e0, s32 *, 4) != 0) {
        func_ov031_0221c4ac();
        M2C_FIELD(&data_ov031_0224e6e0, s32 *, 4) = 0;
    }
}
#pragma thumb off
