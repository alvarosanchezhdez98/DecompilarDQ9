#include <m2c.h>

M2C_UNK func_ov016_0218be7c();
extern M2C_UNK data_027e0000;
extern M2C_UNK data_ov016_0219d0c0;

void func_ov016_0218be1c(void) {
    if (M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x14) == 0) {
        M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x14) = 1;
        func_ov016_0218be7c();
    }
    M2C_FIELD(&data_027e0000, s32 *, 0x3FF8) = (s32) (M2C_FIELD(&data_027e0000, s32 *, 0x3FF8) | 1);
}
