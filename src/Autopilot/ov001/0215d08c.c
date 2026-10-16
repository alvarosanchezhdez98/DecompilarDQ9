#include <m2c.h>

s32 func_0203cf4c();
void * func_0203dce4();
s32 func_ov017_021d60f4();
extern M2C_UNK data_ov001_02165880;

s32 func_ov001_0215d08c(s32 arg0) {
    s32 temp_r1;
    s32 temp_r4;
    s32 temp_r5;
    void *temp_r0;

    temp_r5 = func_ov017_021d60f4();
    temp_r4 = func_ov017_021d60f4(arg0 + 8);
    temp_r0 = func_0203dce4(func_0203cf4c(), M2C_FIELD((M2C_FIELD(&data_ov001_02165880, s32 *, 4) + (temp_r5 * 0x10)), s32 *, 4));
    if (temp_r0 == NULL) {
        return 0;
    }
    temp_r1 = M2C_FIELD((M2C_FIELD(&data_ov001_02165880, s32 *, 4) + (temp_r4 * 0x10)), s32 *, 0xC);
    if (temp_r1 == 0) {
        return 0;
    }
    M2C_FIELD(temp_r0, s32 *, 0x10) = temp_r1;
    return 1;
}
