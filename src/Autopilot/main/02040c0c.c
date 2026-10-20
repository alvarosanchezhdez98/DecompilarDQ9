#include <m2c.h>


void func_02040bfc(void *arg0, s32 arg1) {
    void *temp_r0;
    void *temp_r2;
    void *temp_r2_2;

    temp_r2 = M2C_FIELD(arg0, void **, 0x14);
    if (temp_r2 != NULL) {
        M2C_FIELD(temp_r2, s32 *, 0x8C) = arg1;
        return;
    }
    temp_r2_2 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_r2_2 != NULL) {
        M2C_FIELD(temp_r2_2, s32 *, 0xC8) = arg1;
        return;
    }
    temp_r0 = M2C_FIELD(arg0, void **, 0x1C);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 0x2EC) = arg1;
    }
}
