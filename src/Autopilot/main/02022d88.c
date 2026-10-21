#include <m2c.h>

M2C_UNK _Z16SetSubBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
s32 func_ov017_0218b5b0();
M2C_UNK func_02022bb0(void *);

void func_02022d78(void *arg0, u8 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0x9C3) != 0) {
        _Z16SetSubBrightnessP13GameResourcesii(func_ov017_0218b5b0(), -0x10, 0);
    }
    func_02022bb0(arg0);
    M2C_FIELD(arg0, u8 *, 0xA34) = (u8) M2C_FIELD(arg0, u8 *, 0x9C1);
    M2C_FIELD(arg0, u8 *, 0x9C1) = arg1;
    M2C_FIELD(arg0, u8 *, 0x9C3) = 1U;
    M2C_FIELD(arg0, s8 *, 0x9C2) = 0;
}
