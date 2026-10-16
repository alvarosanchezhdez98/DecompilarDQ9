#include <m2c.h>

M2C_UNK _ZN13SafeAllocator11CreateTypeBEPvji(s32, s32, s32, M2C_UNK);
s32 _ZN13SafeAllocator8AllocateEj(s32, s32);
s32 _ZNK13SafeAllocator24GetMaxPossibleAllocationEv(s32);
M2C_UNK func_0207dfc8(s32, s32);

void func_ov025_021e8a74(void *arg0) {
    s32 temp_r0_2;
    u8 temp_r0;
    u8 temp_r1;

    temp_r0 = M2C_FIELD(arg0, u8 *, 0x30);
    if (temp_r0 == 3) {
        return;
    }
    temp_r0_2 = _ZNK13SafeAllocator24GetMaxPossibleAllocationEv(M2C_FIELD((arg0 + (temp_r0 * 4)), s32 *, 0x10));
    _ZN13SafeAllocator11CreateTypeBEPvji(M2C_FIELD((arg0 + ((M2C_FIELD(arg0, u8 *, 0x30) + 1) * 4)), s32 *, 0x10), _ZN13SafeAllocator8AllocateEj(M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x30) * 4)), s32 *, 0x10), temp_r0_2), temp_r0_2, 4);
    temp_r1 = M2C_FIELD(arg0, u8 *, 0x30);
    func_0207dfc8(M2C_FIELD((arg0 + (temp_r1 * 4)), s32 *, 0x20), M2C_FIELD((arg0 + ((temp_r1 + 1) * 4)), s32 *, 0x20));
    M2C_FIELD(arg0, u8 *, 0x30) = (u8) (M2C_FIELD(arg0, u8 *, 0x30) + 1);
}
