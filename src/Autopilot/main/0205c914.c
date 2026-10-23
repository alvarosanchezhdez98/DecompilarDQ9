#include <m2c.h>

M2C_UNK func_0202f380(s32, M2C_UNK);
s32 func_020421a0();
M2C_UNK func_02042b10(s32, void *);
M2C_UNK func_02042b1c(s32);
M2C_UNK func_0205c5b0(void *, M2C_UNK);
s32 func_0205cde8(void *);

void func_0205c904(void *arg0, M2C_UNK arg1) {
    s32 temp_r0;

    if ((M2C_FIELD(arg0, u8 *, 0x233) != 0) && (M2C_FIELD(arg0, u8 *, 0x234) != 0)) {
        temp_r0 = func_020421a0();
        func_02042b10(temp_r0, arg0 + 0xB4);
        func_0202f380(temp_r0 + 0x19E0, arg1);
        func_02042b1c(temp_r0);
        if (func_0205cde8(arg0) == 0) {
            return;
        }
        func_0205c5b0(arg0 + 0x1C, arg1);
    }
}
