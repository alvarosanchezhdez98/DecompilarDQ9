#include <m2c.h>

M2C_UNK memcpy(s32);

void func_02049410(void *arg0, s32 arg1, u32 arg2) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 == NULL) {
        return;
    }
    if (arg2 >= 0x10U) {
        return;
    }
    memcpy(temp_r0 + 0x24);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x13C), s8 *, 0x34) = (s8) arg2;
}
