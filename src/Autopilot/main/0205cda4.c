#include <m2c.h>

void *func_020421a0();
M2C_UNK func_02042b10(void *, s32);
M2C_UNK func_02042b1c(void *);
s32 func_0205cd6c(void *);

void func_0205cd94(s32 arg0) {
    void *temp_r0;

    temp_r0 = func_020421a0();
    func_02042b10(temp_r0, arg0 + 0xB4);
    if (func_0205cd6c(temp_r0 + 0x19E0) == 0) {
        M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x1E20), s32 *, 8) = 2;
        M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x1E20), s32 *, 0x14) = 0x1000;
    }
    func_02042b1c(temp_r0);
}
