#include <m2c.h>

void *func_0200ff58(M2C_UNK, u16);
M2C_UNK func_02039858(void *, s8);
M2C_UNK func_0203986c(void *, s8);
M2C_UNK func_020546a0(void *, s8);
M2C_UNK func_020546b4(void *, s8);

void func_ov017_021ce3ac(s32 arg0, void *arg1, M2C_UNK arg2) {
    void *temp_r0;

    temp_r0 = func_0200ff58(arg2, M2C_FIELD(arg1, u16 *, 4));
    if (temp_r0 == NULL) {
        return;
    }
    func_020546a0(temp_r0, M2C_FIELD(arg1, s8 *, 6));
    func_020546b4(temp_r0, M2C_FIELD(arg1, s8 *, 7));
    func_02039858(temp_r0, M2C_FIELD(arg1, s8 *, 8));
    func_0203986c(temp_r0, M2C_FIELD(arg1, s8 *, 9));
    M2C_FIELD(temp_r0, u8 *, 0x2D2) = (u8) M2C_FIELD(arg1, u8 *, 0xA);
}
