#include <m2c.h>
#pragma optimization_level 4

void *func_020421a0();
M2C_UNK func_0205d6a0(void *, M2C_UNK);
s32 func_020e0434(void *, s32);
M2C_UNK func_ov003_02159250(void *, s32);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_02191108(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_ov017_021d243c(M2C_UNK);

void func_ov003_0215af00(void *arg0) {
    void *temp_r5;
    u8 temp_r6;

    temp_r5 = func_020421a0();
    temp_r6 = M2C_FIELD(arg0, u8 *, 0x580);
    if (temp_r6 == 0) {
        func_0205d6a0(arg0 + 0xF4, 1);
        func_ov003_02159250(arg0, func_020e0434(arg0 + 0x64, 0x442));
        M2C_FIELD(arg0, u8 *, 0x580) = (u8) (M2C_FIELD(arg0, u8 *, 0x580) + 1);
    }
    if ((temp_r6 == 1) && (M2C_FIELD(temp_r5, s32 *, 0x998) == 0)) {
        func_ov017_021d243c(0);
        func_ov017_02191108(func_ov017_0218b5b0(), 1, 1, 1, 1);
        M2C_FIELD(arg0, s8 *, 0x588) = 0xB;
        M2C_FIELD(arg0, u8 *, 0x580) = 0U;
    }
}
