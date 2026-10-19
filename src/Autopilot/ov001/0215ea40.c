#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_02012dd0(M2C_UNK *);
s32 func_ov017_021d60f4();
extern M2C_UNK data_02114e20;
extern s32 data_ov001_021658b8[8];

s32 func_ov001_0215ea40(void) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;

    temp_r0 = func_ov017_021d60f4();
    if ((temp_r0 < 0) || (temp_r0 >= 8)) {
        return 0;
    }
    temp_r5 = data_ov001_021658b8[temp_r0];
    if (temp_r5 == 0) {
        return 0;
    }
    temp_r0_2 = _ZNK13SafeAllocator18GetSignedAllocatorEv(temp_r5);
    if (temp_r0_2 != 0) {
        _ZN13SafeAllocator7DestroyEv(temp_r5);
        func_02012da4(&data_02114e20, temp_r0_2);
    }
    func_02012dd0(&data_02114e20);
    return 1;
}
