#include <m2c.h>

M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, s32);
M2C_UNK memcpy(s32 *, s32, M2C_UNK);

void func_0204a8f4(s32 arg0, s32 arg1) {
    s32 sp4;
    s32 sp0;

    memcpy(&sp0, arg1, 4);
    memcpy(arg0 + 4, arg1 + 4, 2);
    memcpy(arg0 + 6, arg1 + 6, 2);
    memcpy(arg0 + 8, arg1 + 8, 2);
    memcpy(arg0 + 0xA, arg1 + 0xA, 1);
    memcpy(arg0 + 0xB, arg1 + 0xB, 1);
    memcpy(&sp4, arg1 + 0xC, 4);
    _Z25CleanInvalidateCacheRangePKvj(arg1 + 0x10, sp4);
}
