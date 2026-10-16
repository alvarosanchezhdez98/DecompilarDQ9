#include <m2c.h>

s32 func_0205ec34();
M2C_UNK func_0206df6c(s32, s32, s32, M2C_UNK);

void func_02052d7c(void *arg0, s32 arg1, s16 arg2) {
    s32 temp_r0_2;
    void *temp_r0;
    void *temp_r1;

    temp_r0 = M2C_FIELD(arg0, void **, 0x150);
    if ((temp_r0 != NULL) && (arg2 != M2C_FIELD((temp_r0 + (arg1 * 2)), s16 *, 0x488))) {
        if ((arg1 != 7) && (arg1 != 8)) {
            temp_r0_2 = func_0205ec34();
            func_0206df6c(temp_r0_2, temp_r0_2 + 0x8C, 0x113F, 1);
        }
        M2C_FIELD((M2C_FIELD(arg0, void **, 0x150) + (arg1 * 2)), s16 *, 0x488) = arg2;
        if (arg1 != 9) {
            return;
        }
        temp_r1 = M2C_FIELD(arg0, void **, 0x150);
        if (temp_r1 != NULL) {
            M2C_FIELD(temp_r1, s8 *, 0x56E) = 1;
        }
    }
}
