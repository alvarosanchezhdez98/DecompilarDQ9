#include <m2c.h>

s32 func_020421a0();
M2C_UNK func_02042b10(s32, s32);
M2C_UNK func_02042b1c(s32);
s32 func_0205cd6c(s32);

s32 func_0205cde8(s32 arg0) {
    s32 temp_r0;
    s32 var_r5;

    temp_r0 = func_020421a0();
    func_02042b10(temp_r0, arg0 + 0xB4);
    if (func_0205cd6c(temp_r0 + 0x19E0) != 0) {
        var_r5 = 1;
    } else {
        var_r5 = 0;
    }
    func_02042b1c(temp_r0);
    return var_r5;
}
