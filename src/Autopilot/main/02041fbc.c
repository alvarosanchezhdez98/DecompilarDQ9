#include <m2c.h>

s32 func_020d2ff0();
s32 sprintf(s32, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_020effd7;

s32 func_02041fac(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_r4;

    temp_r4 = arg0 + func_020d2ff0();
    return (temp_r4 + sprintf(temp_r4, &data_020effd7, arg2, arg1)) - arg0;
}
