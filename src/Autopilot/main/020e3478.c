#include <m2c.h>

s32 func_0202ae18();
s32 func_0202b7d8();
s32 func_0202c1a4(s32);
M2C_UNK func_020e303c(u8 *);
u8 *func_020e3054(M2C_UNK, M2C_UNK);

void func_020e3468(M2C_UNK arg0, M2C_UNK arg1) {
    s32 temp_r5;
    u8 *temp_r0;

    temp_r5 = func_0202ae18();
    if (func_0202b7d8() == 0) {
        return;
    }
    temp_r0 = func_020e3054(arg0, arg1);
    if (temp_r0 == NULL) {
        return;
    }
    if (*temp_r0 != func_0202c1a4(temp_r5)) {
        return;
    }
    func_020e303c(temp_r0);
}
