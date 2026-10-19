#include <m2c.h>

M2C_UNK _ZN13SafeAllocator11CreateTypeAEPvj(s32, s32, s32);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv();
s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
u32 _ZNK13SafeAllocator24GetMaxPossibleAllocationEv();
s32 func_02012d88(M2C_UNK *, s32);
s32 func_02012dd0(M2C_UNK *);
s32 func_ov017_021d60f4();
extern M2C_UNK data_02114e20;
extern s32 data_ov001_021658b8[8];

s32 func_ov001_0215e9b0(void) {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r5;

    temp_r0 = func_ov017_021d60f4();
    if ((temp_r0 < 0) || (temp_r0 >= 8)) {
        return 0;
    }
    temp_r5 = func_02012dd0(&data_02114e20);
    if ((*data_ov001_021658b8 != 0) && (_ZNK13SafeAllocator24GetMaxPossibleAllocationEv() <= 0x14U)) {
        return 0;
    }
    temp_r4 = _ZN13SafeAllocator8AllocateEj(*data_ov001_021658b8, 0x14);
    _ZN13SafeAllocator21ResetAllocatorPointerEv();
    _ZN13SafeAllocator11CreateTypeAEPvj(temp_r4, func_02012d88(&data_02114e20, temp_r5), temp_r5);
    return 1;
}
