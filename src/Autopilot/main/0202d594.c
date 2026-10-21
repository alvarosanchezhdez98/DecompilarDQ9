#include <m2c.h>

s32 func_020d559c(M2C_UNK (*)(), M2C_UNK);
M2C_UNK func_0202c848();
M2C_UNK func_0202d5ec();
M2C_UNK func_0202dd28();
M2C_UNK func_0202dd98();
extern M2C_UNK data_021015a0;

void func_0202d584(void *arg0) {
    s32 var_r0;

    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        func_0202c848();
        func_0202dd98();
        return;
    }
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 3;
    if (func_020d559c(func_0202d5ec, 0) == 2) {
        var_r0 = 1;
    } else {
        func_0202c848();
        func_0202dd28();
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
    }
}
