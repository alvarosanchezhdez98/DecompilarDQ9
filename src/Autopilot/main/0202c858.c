#include <m2c.h>

extern M2C_UNK data_021015a0;

void func_0202c848(s32 arg0) {
    if ((u32) (M2C_FIELD(&data_021015a0, s32 *, 0x10) - 9) > 1U) {
        M2C_FIELD(&data_021015a0, s32 *, 0x48) = arg0;
    }
}
