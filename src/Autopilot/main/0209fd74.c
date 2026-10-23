#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, M2C_UNK);
M2C_UNK func_020c9be0();
M2C_UNK func_ov017_021d4c04(void *, s32, s32, M2C_UNK, s32, s32);
M2C_UNK func_0209dc4c(void *);
extern void *data_02109d88;

void func_0209fd64(void *arg0, M2C_UNK arg1, s32 arg2, s32 arg3) {
    s32 temp_r4;
    s32 temp_r5;

    data_02109d88 = arg0;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
    M2C_FIELD(arg0, s32 *, 0xC) = arg3;
    temp_r4 = _ZN13SafeAllocator8AllocateEj(arg1, 0x400);
    temp_r5 = _ZN13SafeAllocator8AllocateEj(arg1, 0x1800);
    if ((temp_r4 != 0) && (temp_r5 != 0)) {

    } else {
        func_020c9be0();
    }
    func_ov017_021d4c04(arg0 + 0x10, M2C_FIELD(arg0, s32 *, 8), temp_r4, 0x80, temp_r5, 0x200);
    func_0209dc4c(arg0 + 0x10);
}
