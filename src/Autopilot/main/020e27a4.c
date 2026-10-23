#include <m2c.h>

M2C_UNK func_0205ae8c(s32);
u32 func_020e1780(s32);
M2C_UNK func_020e27ec(s32, u16, s16, s16);

u32 func_020e2794(void *arg0, s32 arg1) {
    s32 temp_r0_2;
    u32 temp_r0;

    temp_r0 = (u32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), u8 *, 0x3F) << 0x1F) >> 0x1F;
    if (temp_r0 == 0) {
        return temp_r0;
    }
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_r0_2 != 0) {
        func_020e27ec(temp_r0_2, M2C_FIELD(arg0, u16 *, 0x1C), M2C_FIELD(arg0, s16 *, 0x18), M2C_FIELD(arg0, s16 *, 0x1A));
        if (arg1 != 0) {
            func_0205ae8c(arg1);
        }
    }
    return func_020e1780(M2C_FIELD(arg0, s32 *, 0x10));
}
