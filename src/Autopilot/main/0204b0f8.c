#include <m2c.h>

M2C_UNK func_0204b04c(void *, s32);
M2C_UNK func_0204b088(void *, s32);

void func_0204b0e8(void *arg0, s32 arg1) {
    s32 var_r4;

    var_r4 = arg1;
    if (var_r4 == 0) {
        var_r4 = M2C_FIELD(arg0, s32 *, 0x14);
    }
    if (var_r4 == 0) {
        return;
    }
    func_0204b04c(arg0, var_r4);
    func_0204b088(arg0, var_r4);
}
