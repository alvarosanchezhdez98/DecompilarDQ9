#include <m2c.h>

s32 func_0202ae18();
s32 func_0202c540();
s32 func_0202c578(s32, M2C_UNK);

s32 func_ov017_021959b4(void) {
    s32 temp_r4;

    temp_r4 = func_0202ae18();
    if ((func_0202c540() != 0) && (func_0202c578(temp_r4, 0) != 0)) {
        return 1;
    }
    return 0;
}
