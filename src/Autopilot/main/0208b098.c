#include <m2c.h>

M2C_UNK func_0208ab34(void *, s32);
M2C_UNK func_0208b0f8();
s32 func_0208b4d4(void *);

s32 func_0208b088(void *arg0) {
    s32 temp_r0;
    s32 var_r1;

    func_0208b0f8();
    if (M2C_FIELD(arg0, u8 *, 0x9C) == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    M2C_FIELD(arg0, s32 *, 0x20) = var_r1;
    temp_r0 = func_0208b4d4(arg0);
    func_0208ab34(arg0 + 4, temp_r0);
    func_0208ab34(arg0 + 0x24, temp_r0);
    func_0208ab34(arg0 + 0x40, temp_r0);
    func_0208ab34(arg0 + 0x5C, temp_r0);
    func_0208ab34(arg0 + 0x78, temp_r0);
    return 1;
}
