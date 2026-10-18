#include <m2c.h>


void func_0202f6d4(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x440);
    if (temp_r1 == NULL) {
        return;
    }
    M2C_FIELD(temp_r1, s32 *, 0x10) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x440), s32 *, 0x14) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x440), s32 *, 8) = 3;
}
