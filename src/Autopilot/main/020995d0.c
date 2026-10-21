#include <m2c.h>

s32 _ZNK6Script9Parameter5ToIntEv();
s32 func_02012d88(M2C_UNK *, s32);
extern void *data_02109924;
extern M2C_UNK data_02114e20;

s32 func_020995c0(void) {
    s32 temp_r0;
    void *temp_r5;

    temp_r0 = _ZNK6Script9Parameter5ToIntEv();
    temp_r5 = data_02109924;
    M2C_FIELD(temp_r5, s32 *, 0) = func_02012d88(&data_02114e20, temp_r0 * 0x10);
    M2C_FIELD(temp_r5, s32 *, 8) = temp_r0;
    return 1;
}
