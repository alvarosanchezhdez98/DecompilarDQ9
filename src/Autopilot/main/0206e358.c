#include <m2c.h>

M2C_UNK func_0206df6c(s32, s32, s32, M2C_UNK);
s32 func_0206e3e8(s32, s16);

void func_0206e348(s32 arg0, s32 arg1, M2C_UNK arg2) {
    s32 temp_r0;

    temp_r0 = func_0206e3e8(arg0, arg1);
    if ((s32) (temp_r0 - 0x11) < 0) {
        return;
    }
    func_0206df6c(arg0, arg0 + 0x8C, temp_r0 + 0xBF1, arg2);
}
