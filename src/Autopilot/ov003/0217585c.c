#include <m2c.h>

M2C_UNK func_0205ac40(void *, s32);

void func_ov003_0217585c(void *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    s32 temp_lr;

    temp_lr = (arg3 * 0x28) + M2C_FIELD(arg0, s32 *, 0x830);
    M2C_FIELD(temp_lr, u8 *, 0x22) = arg4;
    M2C_FIELD(temp_lr, s32 *, 0x14) = (s32) (arg1 << 0xC);
    M2C_FIELD(temp_lr, s32 *, 0x18) = (s32) (arg2 << 0xC);
    func_0205ac40(arg0 + 0x7D8, temp_lr);
}
