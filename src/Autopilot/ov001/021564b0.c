#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _Z17SetMainBrightnessP13GameResourcesii(void *, M2C_UNK, M2C_UNK);
void *func_020421a0();
M2C_UNK func_02043124();
M2C_UNK func_02046a8c(s32, s32);
s32 func_020704fc();
M2C_UNK func_020708c8(s32, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021bb27c(void *);
M2C_UNK func_ov001_02156b20(void *);

u16 func_ov001_021564b0(void *arg0) {
    void *temp_r0;
    void *temp_r5;

    temp_r0 = func_ov017_0218b5b0();
    if (M2C_FIELD(temp_r0, u8 *, 0x42E2) != 0) {
        func_02046a8c(M2C_FIELD(temp_r0, s32 *, 0x36FC), M2C_FIELD(temp_r0, s32 *, 0x3718));
        func_020708c8(func_020704fc(), 0xF);
        _Z17SetMainBrightnessP13GameResourcesii(temp_r0, 0, 0xF);
        temp_r5 = func_020421a0();
        func_02043124();
        M2C_FIELD(temp_r5, s8 *, 0x19BE) = 0;
        func_ov001_02156b20(arg0);
        func_ov017_021bb27c(arg0);
        M2C_FIELD(arg0, s8 *, 1) = 1;
    }
    return M2C_FIELD(arg0, u16 *, 0xA);
}
