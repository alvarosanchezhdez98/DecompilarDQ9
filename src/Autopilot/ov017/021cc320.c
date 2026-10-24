#include <m2c.h>

s32 func_0200ff1c(M2C_UNK, u8);
M2C_UNK func_020535f4();

void func_ov017_021cc320(s32 arg0, void *arg1, M2C_UNK arg2) {
    if (func_0200ff1c(arg2, M2C_FIELD(arg1, u8 *, 4)) == 0) {
        return;
    }
    func_020535f4();
}
