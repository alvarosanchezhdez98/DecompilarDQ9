#include <m2c.h>

M2C_UNK func_020a212c(void *, M2C_UNK);
s32 func_020a3570();

void func_020a20f0(void *arg0) {
    if (func_020a3570() != 0) {
        M2C_FIELD(arg0, u8 *, 0x244) = (u8) (M2C_FIELD(arg0, u8 *, 0x244) | 8);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x238) == 0) {
        return;
    }
    func_020a212c(arg0, 1);
}
