#include <m2c.h>


void func_02049390(void *arg0, s8 arg1) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if ((temp_r0 != NULL) && (arg1 != 0xFF)) {
        M2C_FIELD(temp_r0, s8 *, 0x1C) = arg1;
    }
}
