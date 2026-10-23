#include <m2c.h>

u32 func_0203aba8(void *, s16, void *);
M2C_UNK func_0203ac10(void *, void *, M2C_UNK);
s32 func_0209c140();
u32 func_0209c678(void *, M2C_UNK);

u32 func_0209c5e8(void *arg0) {
    u32 temp_r0;
    u32 temp_r0_2;

    temp_r0_2 = (u32) (M2C_FIELD(arg0, u8 *, 0xC8) << 0x1D) >> 0x1F;
    if (temp_r0_2 != 0) {
        return temp_r0_2;
    }
    if (func_0209c140() != 0) {
        return func_0209c678(arg0, 0);
    }
    temp_r0 = M2C_FIELD(arg0, u32 *, 0xB0);
    if (temp_r0 == 1) {
        func_0203ac10(arg0, arg0 + 0xBC, 0);
        return func_0203aba8(arg0, M2C_FIELD(arg0, s16 *, 0xB8), arg0 + 0xBC);
    }
    if (temp_r0 != 2) {
        return temp_r0;
    }
    func_0203ac10(arg0, arg0 + 0xC0, 0);
    return func_0203aba8(arg0, M2C_FIELD(arg0, s16 *, 0xBA), arg0 + 0xC0);
}
