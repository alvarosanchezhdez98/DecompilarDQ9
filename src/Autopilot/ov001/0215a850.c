#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov001_0215a79c();
M2C_UNK func_ov001_0215a8dc();
extern M2C_UNK data_ov001_02165880;

void func_ov001_0215a850(M2C_UNK arg0) {
    s32 temp_r0;

    M2C_FIELD(&data_ov001_02165880, s32 *, 8) = _ZN13SafeAllocator8AllocateEj(arg0, 0x260);
    M2C_FIELD(&data_ov001_02165880, s32 *, 0x24) = _ZN13SafeAllocator8AllocateEj(arg0, 0xA28);
    M2C_FIELD(&data_ov001_02165880, s32 *, 0x20) = _ZN13SafeAllocator8AllocateEj(arg0, 0x700);
    M2C_FIELD(&data_ov001_02165880, s32 *, 0x1C) = _ZN13SafeAllocator8AllocateEj(arg0, 0x84C0);
    temp_r0 = _ZN13SafeAllocator8AllocateEj(arg0, 0x200);
    M2C_FIELD(&data_ov001_02165880, s32 *, 4) = temp_r0;
    memset(temp_r0, 0, 0x200);
    func_ov001_0215a79c();
    func_ov001_0215a8dc();
}
