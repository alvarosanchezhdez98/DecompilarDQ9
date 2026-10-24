#include <m2c.h>

s32 func_0200ff1c(M2C_UNK, s32);
s32 func_02053c6c();
M2C_UNK func_0208386c(s32, s8);

void func_ov017_021d0164(s32 arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_r0;

    if (func_0200ff1c(arg2, M2C_FIELD(arg1, s32 *, 4)) == 0) {
        return;
    }
    temp_r0 = func_02053c6c();
    if (temp_r0 == 0) {
        return;
    }
    func_0208386c(temp_r0, M2C_FIELD(arg1, s8 *, 8));
}
