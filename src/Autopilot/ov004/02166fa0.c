#include <m2c.h>

M2C_UNK func_0208bf28(s32, s32, u8);
s32 func_ov004_02165e70(u8, M2C_UNK);
s32 func_ov004_021666bc(u8, u8 *);

s32 func_ov004_02166fa0(u8 arg0) {
    u8 sp0;
    s32 temp_r0_2;
    s32 var_r4;
    u8 temp_r0;
    u8 var_r5;

    var_r5 = arg0;
    var_r4 = func_ov004_021666bc(arg0, &sp0);
    temp_r0 = var_r5;
    var_r5 = sp0;
    temp_r0_2 = func_ov004_02165e70(temp_r0, 7);
    if (temp_r0_2 != 0) {
        func_0208bf28(temp_r0_2 + 0x34, var_r4, var_r5);
    }
    return 0;
}
