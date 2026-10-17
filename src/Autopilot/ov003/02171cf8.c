#include <m2c.h>

void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021b1e24(void *, s32);

void func_ov003_02171cf8(void *arg0) {
    void *temp_r0;
    void *temp_r6;

    temp_r0 = func_ov017_0218b5b0();
    temp_r6 = M2C_FIELD(temp_r0, void **, 0x3B48);
    func_ov017_021b1e24(temp_r6, M2C_FIELD(temp_r0, s32 *, 0x36FC));
    if (M2C_FIELD(temp_r0, s32 *, 0x4494) != 0) {
        return;
    }
    if (M2C_FIELD(temp_r6, u8 *, 0x28) != 0) {
        M2C_FIELD(arg0, u8 *, 0x730) = (u8) (M2C_FIELD(arg0, u8 *, 0x730) & ~2);
        M2C_FIELD(arg0, s8 *, 0x733) = 1;
    }
    M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x4494) = 1;
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 0x731) = 2;
    M2C_FIELD(arg0, s8 *, 0x732) = 3;
}
