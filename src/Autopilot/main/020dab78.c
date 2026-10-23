#include <m2c.h>

s32 func_02057924();
M2C_UNK func_02057e6c(s32, M2C_UNK, s32, M2C_UNK, s32, s32);
M2C_UNK func_0207df90(s32);
M2C_UNK func_0207dfac(s32);

s32 func_020dab68(void *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r5;
    s32 temp_r6;

    temp_r0 = func_02057924();
    temp_r5 = M2C_FIELD(arg0, s32 *, 0);
    temp_r6 = M2C_FIELD(arg0, s32 *, 4);
    if ((temp_r0 != 0) && (temp_r5 != 0) && (temp_r6 != 0)) {
        func_0207df90(temp_r6);
        func_02057e6c(temp_r0, 0x16, temp_r5, arg1, arg2, temp_r6);
        func_0207dfac(temp_r6);
        return 1;
    }
    return 0;
}
