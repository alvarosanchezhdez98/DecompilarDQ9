#include <m2c.h>

s32 ov00_021EA1CC();
M2C_UNK strcpy(M2C_UNK, s32);
s32 strlen();

s32 ov00_021EA278(s32 arg0, s32 arg1, M2C_UNK arg2, s32 arg3) {
    s32 temp_r0;

    temp_r0 = ov00_021EA1CC();
    if (temp_r0 == 0) {
        return 0;
    }
    if (strlen() >= arg3) {
        return 0;
    }
    strcpy(arg2, temp_r0);
    return 1;
}
