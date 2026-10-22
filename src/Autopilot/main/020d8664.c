#include <m2c.h>

s32 _Z25DisableSpecificInterruptsj(M2C_UNK);
extern M2C_UNK data_0214e4a0;

void func_020d8654(void) {
    s32 var_r2;

    M2C_FIELD(&data_0214e4a0, s32 *, 4) = (s32) (M2C_FIELD(&data_0214e4a0, s32 *, 4) * 2);
    if (_Z25DisableSpecificInterruptsj(4) & 4) {
        var_r2 = 1;
    } else {
        var_r2 = 0;
    }
    M2C_FIELD(&data_0214e4a0, s32 *, 4) = (s32) (M2C_FIELD(&data_0214e4a0, s32 *, 4) | var_r2);
}
