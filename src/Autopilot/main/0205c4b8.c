#include <m2c.h>

M2C_UNK func_0205bb04(void *, s32);
s32 func_0205bb84(void *);

void func_0205c4a8(void *arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r1;
    s32 temp_r5;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x14) + arg1;
    M2C_FIELD(arg0, s32 *, 0x14) = temp_r0;
    temp_r1 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_r1 <= temp_r0) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) - temp_r1);
    } else if (temp_r0 < 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) + temp_r1);
    }
    temp_r5 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_r5 > func_0205bb84(arg0)) {
        return;
    }
    func_0205bb04(arg0, temp_r5 - 1);
}
