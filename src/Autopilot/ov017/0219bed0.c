#include <m2c.h>
#pragma optimization_level 4

s32 func_ov017_0219bddc(u8 *);
M2C_UNK func_ov017_0219bf04(u8, M2C_UNK);

s32 func_ov017_0219bed0(M2C_UNK arg0) {
    u8 sp0;
    s32 temp_r0;

    sp0 = 0;
    temp_r0 = func_ov017_0219bddc(&sp0);
    if (temp_r0 != 0) {
        func_ov017_0219bf04(sp0, arg0);
    }
    return temp_r0;
}
