#include <m2c.h>

s32 func_ov000_02161318(void *, s32);
M2C_UNK func_ov000_02170fd0(s32, M2C_UNK);
M2C_UNK func_ov000_02174c14(void *);
s32 func_ov000_0217f7d4();
M2C_UNK func_ov000_0217fa60(void *);

void func_ov000_0217f78c(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = func_ov000_0217f7d4();
    temp_r0_2 = func_ov000_02161318(arg0, temp_r0);
    if (temp_r0_2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x17C) = temp_r0;
        func_ov000_02170fd0(temp_r0_2, 0);
        return;
    }
    func_ov000_0217fa60(arg0);
    func_ov000_02174c14(arg0);
}
