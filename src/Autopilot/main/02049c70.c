#include <m2c.h>


void func_02049c60(void *arg0, void *arg1) {
    void *temp_r1;
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r2 == NULL) {
        return;
    }
    M2C_FIELD(temp_r2, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 4);
    temp_r1 = M2C_FIELD(arg0, void **, 0x13C);
    M2C_FIELD(temp_r1, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r1, s32 *, 0x20) & ~1);
}
