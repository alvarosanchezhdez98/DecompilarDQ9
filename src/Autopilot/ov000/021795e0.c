#include <m2c.h>

void *func_020421a0();
M2C_UNK func_0205d5d0(s32, M2C_UNK, s32, M2C_UNK, s32);
M2C_UNK func_ov000_0217964c(s32, s32);
M2C_UNK func_ov000_0217979c(s32, s32, s32);
s32 func_ov000_0217f8c0();
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov000_021795e0(s32 arg0) {
    s32 temp_r0;
    s32 temp_r5;

    temp_r0 = func_ov000_0217f8c0();
    func_ov000_0217964c(arg0, temp_r0);
    temp_r5 = M2C_FIELD(func_020421a0(), s32 *, 0x5C);
    memset(temp_r5, 0, 0x960);
    func_ov000_0217979c(arg0, temp_r0, temp_r5);
    func_0205d5d0(arg0 + 0x188, 0x11, temp_r5, 1, 0);
}
