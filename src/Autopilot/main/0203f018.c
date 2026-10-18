#include <m2c.h>

s32 func_02040468(s32, s16);

s32 func_0203f008(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_r0 == 0) {
        return 0;
    }
    return func_02040468(temp_r0, M2C_FIELD(arg0, s16 *, 0x28));
}
