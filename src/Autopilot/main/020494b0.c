#include <m2c.h>


u8 func_020494a0(void *arg0) {
    u8 var_r0;
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r1 == NULL) {
        return 0xFFU;
    }
    var_r0 = M2C_FIELD(temp_r1, u8 *, 0x4C);
    if (var_r0 == 0xFF) {
        var_r0 = M2C_FIELD(temp_r1, u8 *, 0x4D);
    }
    return var_r0;
}
