#include <m2c.h>

void *func_020421a0();
M2C_UNK func_02042b10(void *, s32);
M2C_UNK func_02042b1c(void *);

void func_0205ce94(s32 arg0) {
    void *temp_r0;
    void *temp_r1;

    temp_r0 = func_020421a0();
    func_02042b10(temp_r0, arg0 + 0xB4);
    temp_r1 = M2C_FIELD(temp_r0, void **, 0x1E20);
    if (temp_r1 != NULL) {
        M2C_FIELD(temp_r1, s32 *, 8) = 0;
    }
    func_02042b1c(temp_r0);
}
