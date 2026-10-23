#include <m2c.h>

s32 func_02012fe4();
void *func_0201b600(s32, M2C_UNK, s32);
s32 func_020ae4c8();

void func_020ae694(s32 arg0, M2C_UNK arg1, s32 arg2) {
    u16 temp_r1;
    void *temp_r0;

    if (arg2 == 0) {
        return;
    }
    if (func_020ae4c8() != 0) {
        return;
    }
    temp_r0 = func_0201b600(func_02012fe4(), arg1, arg2);
    if (temp_r0 == NULL) {
        return;
    }
    temp_r1 = M2C_FIELD(temp_r0, u16 *, 2);
    if (arg0 == 0) {
        M2C_FIELD(temp_r0, u16 *, 2) = (u16) (temp_r1 | 4);
        return;
    }
    M2C_FIELD(temp_r0, u16 *, 2) = (u16) (temp_r1 & ~4);
}
