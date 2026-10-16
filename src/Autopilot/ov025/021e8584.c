#include <m2c.h>

M2C_UNK func_0202e95c(s32, s16, u16);
M2C_UNK func_ov000_02160130();
s32 func_ov000_02160f14();

s32 func_ov025_021e8584(void *arg0) {
    func_ov000_02160130();
    func_0202e95c(func_ov000_02160f14(), M2C_FIELD(arg0, s16 *, 8), M2C_FIELD(arg0, u16 *, 0xA));
    return 1;
}
