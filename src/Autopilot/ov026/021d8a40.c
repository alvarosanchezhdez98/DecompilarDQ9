#include <m2c.h>

s32 func_0202ae24();
s32 func_0205e488();
s32 func_0205e4f8(s32, M2C_UNK);

s32 func_ov026_021d8a40(void) {
    s32 temp_r4;

    temp_r4 = func_0202ae24();
    if (func_0205e488() != 0) {
        return 1;
    }
    if (func_0205e4f8(temp_r4, 0x63) == 0) {
        return 1;
    }
    return 0;
}
