#include <m2c.h>

s32 func_020d5004(M2C_UNK (*)());
s32 func_020d5f88(M2C_UNK *);
M2C_UNK func_0202c848();
M2C_UNK func_0202d614();
extern M2C_UNK data_021015a0;
extern M2C_UNK data_02102be0;

void func_0202dd28(void) {
    s32 var_r0;

    if ((M2C_FIELD(&data_021015a0, s32 *, 0x10) == 5) && (func_020d5f88(&data_02102be0) != 0)) {
        func_0202c848();
    }
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 3;
    if (func_020d5004(func_0202d614) == 2) {
        var_r0 = 1;
    } else {
        func_0202c848();
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        M2C_FIELD(&data_021015a0, s32 *, 0x10) = 0xA;
    }
}
