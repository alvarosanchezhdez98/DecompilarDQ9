#include <m2c.h>

M2C_UNK func_0202f6d4(s32);
s32 func_020421a0();
M2C_UNK func_02042b10(s32, s32);
M2C_UNK func_02042b1c(s32);
s32 func_0205ce28(s32);

void func_0205ce50(s32 arg0) {
    s32 temp_r0;

    temp_r0 = func_020421a0();
    func_02042b10(temp_r0, arg0 + 0xB4);
    if (func_0205ce28(temp_r0 + 0x19E0) == 0) {
        func_0202f6d4(temp_r0 + 0x19E0);
    }
    func_02042b1c(temp_r0);
}
