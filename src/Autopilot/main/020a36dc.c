#include <m2c.h>

s32 func_02012d88(M2C_UNK *, u32);
u32 func_02012dd0(M2C_UNK *);
void *func_ov017_0218b5b0();
M2C_UNK func_020a0cc4(u32);
extern M2C_UNK data_02114e20;

s32 func_020a36cc(s32 *arg0, u32 arg1) {
    void *temp_r4;

    temp_r4 = func_ov017_0218b5b0();
    if (func_02012dd0(&data_02114e20) < arg1) {
        func_020a0cc4(arg1);
        M2C_FIELD(temp_r4, s8 *, 0x4490) = 1;
    }
    *arg0 = func_02012d88(&data_02114e20, arg1);
    return 1;
}
