#include <m2c.h>
#pragma optimization_level 4


void func_02049f28(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r1 != NULL) {
        M2C_FIELD(temp_r1, s8 *, 0x56) = 1;
    }
}
