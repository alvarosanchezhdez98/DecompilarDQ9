#include <m2c.h>

M2C_UNK func_020797f8();
s32 func_02079f20(s32, s32, M2C_UNK (*)());

s32 func_02079ee0(s32 arg0, s32 arg1) {
    s32 temp_r0;

    if (arg1 == 0) {
        return 0;
    }
    temp_r0 = func_02079f20(arg0 + 0x18, arg1, func_020797f8);
    if (temp_r0 != 0) {
        return temp_r0;
    }
    return func_02079f20(arg0 + 0x24, arg1, func_020797f8);
}
