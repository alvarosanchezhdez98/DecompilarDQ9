#include <m2c.h>


void func_0202f6a4(void *arg0) {
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0x440);
    if (temp_r2 == NULL) {
        return;
    }
    M2C_FIELD(temp_r2, s32 *, 0x10) = 0x1000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x440), s32 *, 0x14) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x440), s32 *, 8) = 1;
}
