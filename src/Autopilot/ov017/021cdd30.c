#include <m2c.h>

s32 func_0202c1a4(s32);
M2C_UNK func_ov017_021cdccc(u32, u32, void *);

void func_ov017_021cdd30(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 temp_r4;
    u32 temp_r5;

    temp_r4 = M2C_FIELD(arg1, u16 *, 4) << 0x1E;
    temp_r5 = temp_r4 >> 0x1E;
    if (func_0202c1a4(arg4) != (temp_r4 >> 0x1E)) {
        return;
    }
    func_ov017_021cdccc(temp_r5, (u32) (M2C_FIELD(arg1, u16 *, 4) << 0x10) >> 0x12, arg1 + 6);
}
