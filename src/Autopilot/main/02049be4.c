#include <m2c.h>


void func_02049bd4(void *arg0, void *arg1) {
    void *temp_r1;
    void *temp_r3;

    temp_r3 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r3 == NULL) {
        return;
    }
    M2C_FIELD(temp_r3, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x13C), s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 8);
    temp_r1 = M2C_FIELD(arg0, void **, 0x13C);
    M2C_FIELD(temp_r1, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r1, s32 *, 0x20) & ~1);
}
