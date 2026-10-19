#include <m2c.h>


void func_02042c24(void *arg0, s16 arg1, s16 arg2) {
    void *temp_r3;

    temp_r3 = M2C_FIELD(arg0, void **, 0x440);
    if (temp_r3 != NULL) {
        M2C_FIELD(temp_r3, s16 *, 0) = arg1;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x440), s16 *, 2) = arg2;
    }
}
