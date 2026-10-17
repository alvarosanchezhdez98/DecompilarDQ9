#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _Z14StartStaffRollP13SafeAllocator(s32);
M2C_UNK func_0203b4a0(s32, M2C_UNK);
M2C_UNK func_020a1ef0(M2C_UNK);
s32 func_ov017_0218b5b0();
extern s32 data_ov001_021658b8[8];

s32 func_ov001_0216224c(void) {
    func_020a1ef0(5);
    func_0203b4a0(func_ov017_0218b5b0(), 0x1000);
    _Z14StartStaffRollP13SafeAllocator(*data_ov001_021658b8);
    return 1;
}
