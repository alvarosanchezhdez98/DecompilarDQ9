#include <m2c.h>

M2C_UNK _Z13SetBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
void *func_020421a0();
M2C_UNK func_02043124(void *);
M2C_UNK func_02043204();
s32 func_020704fc();
M2C_UNK func_020708c8(s32, M2C_UNK);
s32 func_ov017_0218b5b0();

void func_ov001_02154da0(void) {
    void *temp_r4;

    temp_r4 = func_020421a0();
    func_02043204();
    func_02043124(temp_r4);
    M2C_FIELD(temp_r4, s8 *, 0x19BE) = 0;
    func_020708c8(func_020704fc(), 0);
    _Z13SetBrightnessP13GameResourcesii(func_ov017_0218b5b0(), -0x10, 0);
}
