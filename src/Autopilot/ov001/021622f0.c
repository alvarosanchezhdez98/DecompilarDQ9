#include <m2c.h>

extern M2C_UNK data_ov001_02165880;

void func_ov001_021622f0(void) {
    M2C_FIELD(&data_ov001_02165880, s32 *, 0x28) = (s32) (M2C_FIELD(&data_ov001_02165880, s32 *, 0x28) + 1);
}
