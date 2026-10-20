#include <m2c.h>


void func_0201fbe0(void *arg0, s32 arg1) {
    u8 temp_r2;

    if ((M2C_FIELD(arg0, u8 *, 2) != 0) && (arg1 == 0)) {
        return;
    }
    if ((M2C_FIELD(arg0, u16 *, 4) != 0) && (arg1 == 0)) {
        return;
    }
    temp_r2 = M2C_FIELD(arg0, u8 *, 0);
    if ((temp_r2 != 2) && (temp_r2 != 3)) {
        if ((arg1 != 0) || (M2C_FIELD(arg0, u8 *, 1) == 3)) {
            goto block_12;
        }
    } else {
block_12:
        M2C_FIELD(arg0, u8 *, 1) = 4U;
    }
    M2C_FIELD(arg0, u16 *, 4) = 0U;
}
