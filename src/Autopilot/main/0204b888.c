#include <m2c.h>

M2C_UNK func_0204b620(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32);

void func_0204b878(void *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, u16 arg8) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r1 != 0) {
        func_0204b620(arg0, temp_r1, arg1, arg2, arg3, (s32) arg4, (s32) arg5, (s32) arg6, (s32) arg7, (s32) arg8);
    }
}
