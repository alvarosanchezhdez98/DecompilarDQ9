#include <m2c.h>

s32 func_0202c1a4(s32);
s32 func_02046b24(s32);
M2C_UNK func_ov003_02171fe8(s32, M2C_UNK, void *, u32, s32);
s32 func_ov003_0217f278(s32);

void func_ov017_021d0f94(M2C_UNK arg0, void *arg1, s32 arg2, void *arg3, s32 arg4) {
    s32 temp_r0;

    if ((M2C_FIELD(arg1, u8 *, 4) == func_0202c1a4(arg4)) && (func_02046b24(M2C_FIELD(arg3, s32 *, 0x36FC)) == 0x2A)) {
        temp_r0 = func_ov003_0217f278(M2C_FIELD(arg3, s32 *, 0x3B40));
        if (temp_r0 != 0) {
            func_ov003_02171fe8(temp_r0 + 0x7E0, arg0, arg1 + 7, (u32) (M2C_FIELD(arg1, u8 *, 6) << 0x19) >> 0x19, (s32) M2C_FIELD(arg1, u8 *, 5));
        }
    }
}
