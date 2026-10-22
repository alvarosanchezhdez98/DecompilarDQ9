#include <m2c.h>

M2C_UNK func_02042b98(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32);

void func_02042b3c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1860) = 0xC;
    M2C_FIELD(arg0, s32 *, 0x1864) = 0x10;
    func_02042b98(arg0, 2, 0x92, 0xFC, 0x4A);
    M2C_FIELD(arg0, s8 *, 0x19B2) = 0;
    M2C_FIELD(arg0, s8 *, 0x19B1) = 0;
    M2C_FIELD(arg0, u8 *, 0x195B) = (u8) (M2C_FIELD(arg0, u8 *, 0x195B) | 2);
}
