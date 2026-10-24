#include <m2c.h>
#pragma optimization_level 4

s32 func_02012fe4();
s32 func_0202c540(s32);
M2C_UNK func_ov017_021a01bc(M2C_UNK);

void func_ov017_021d3e7c(s32 arg0, void *arg1, s32 arg2, M2C_UNK arg3, s32 arg4) {
    if (func_0202c540(arg4) == 0) {
        return;
    }
    M2C_FIELD((func_02012fe4() + 0x1840), s32 *, 0xB3C) = (s32) M2C_FIELD(arg1, u8 *, 4);
    func_ov017_021a01bc(arg3);
}
