#include <m2c.h>


void func_0204a00c(void *arg0, s32 arg1) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 0x68) = arg1;
    }
}
