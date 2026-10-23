#include <m2c.h>

M2C_UNK strcpy(s32, s32);

void func_02011a74(s32 arg0, u32 arg1, s32 arg2) {
    s32 temp_r0;

    if (arg2 == 0) {
        return;
    }
    temp_r0 = arg0 + 0x649E;
    if (temp_r0 == 0) {
        return;
    }
    if (arg1 > 3U) {
        return;
    }
    strcpy(temp_r0, arg2);
}
