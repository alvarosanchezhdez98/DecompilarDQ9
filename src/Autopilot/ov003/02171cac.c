#include <m2c.h>

void *func_ov017_0218b5b0();
s32 func_ov017_0219bf74();
M2C_UNK func_ov017_021b1d44(void *, M2C_UNK, M2C_UNK);

void func_ov003_02171cac(void *arg0) {
    s32 temp_r4;
    s8 var_r0;
    void *temp_r5;

    if (!(M2C_FIELD(arg0, u8 *, 0x730) & 2)) {
        var_r0 = 0;
    } else {
        temp_r5 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3B48);
        temp_r4 = func_ov017_0219bf74();
        func_ov017_021b1d44(temp_r5, 0x20, 1);
        M2C_FIELD(temp_r5, s32 *, 8) = temp_r4;
        var_r0 = 9;
    }
    M2C_FIELD(arg0, s8 *, 0) = var_r0;
}
