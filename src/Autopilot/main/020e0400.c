#include <m2c.h>

M2C_UNK func_02072aa8(s32, s32, u32);

s32 func_020e03f0(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        return 0;
    }
    func_02072aa8(arg1, M2C_FIELD(arg0, s32 *, 4), (u32) (M2C_FIELD(arg0, s32 *, 0) << 0x14) >> 0x14);
    return 1;
}
