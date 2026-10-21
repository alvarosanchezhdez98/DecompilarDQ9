#include <m2c.h>

M2C_UNK func_0203cdd8(s32);

void func_02040af0(void *arg0, s32 arg1) {
    s32 temp_r2;
    void *temp_r0;
    void *temp_r2_2;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r2 != 0) {
        func_0203cdd8(temp_r2);
        return;
    }
    temp_r2_2 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_r2_2 != NULL) {
        M2C_FIELD(temp_r2_2, s32 *, 0xB0) = arg1;
        return;
    }
    temp_r0 = M2C_FIELD(arg0, void **, 0x1C);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 0x2D4) = arg1;
    }
}
