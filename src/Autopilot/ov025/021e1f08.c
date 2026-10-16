#include <m2c.h>

s16 func_02049468();
s16 func_0204948c(M2C_UNK);

s16 func_ov025_021e1f08(M2C_UNK arg0, void *arg1) {
    s16 temp_r0;
    s16 var_r0;
    void *temp_r1;

    temp_r0 = func_02049468();
    if (temp_r0 != 0xFF) {
        return temp_r0;
    }
    var_r0 = func_0204948c(arg0);
    if (var_r0 != 0xFF) {
        return var_r0;
    }
    temp_r1 = M2C_FIELD(arg1, void **, 0x14);
    if (temp_r1 != NULL) {
        var_r0 = M2C_FIELD(temp_r1, s16 *, 0xE);
    }
    return var_r0;
}
