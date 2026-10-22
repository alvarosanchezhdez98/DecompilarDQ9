#include <m2c.h>

void *func_0202a9ac(void *, s32);

void func_0202a944(void *arg0, void *arg1) {
    u16 temp_r1;
    void *temp_r0;

    M2C_FIELD(arg1, s32 *, 0x34) = 0;
    temp_r1 = M2C_FIELD(arg0, u16 *, 0x5A);
    if (temp_r1 == 0) {
        M2C_FIELD(arg0, void **, 0x44) = arg1;
        M2C_FIELD(arg1, s8 *, 0x3C) = 0;
        M2C_FIELD(arg0, u16 *, 0x5A) = 1U;
    } else {
        temp_r0 = func_0202a9ac(arg0, temp_r1 - 1);
        if (temp_r0 != NULL) {
            M2C_FIELD(temp_r0, void **, 0x34) = arg1;
            M2C_FIELD(arg1, s8 *, 0x3C) = (s8) M2C_FIELD(arg0, u16 *, 0x5A);
            M2C_FIELD(arg0, u16 *, 0x5A) = (u16) (M2C_FIELD(arg0, u16 *, 0x5A) + 1);
        }
    }
    if (M2C_FIELD(arg1, s32 *, 0) == 1) {
        M2C_FIELD(arg1, void **, 0x48) = arg0;
    }
}
