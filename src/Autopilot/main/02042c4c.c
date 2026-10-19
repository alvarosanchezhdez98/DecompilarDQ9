#include <m2c.h>


void func_02042c3c(void *arg0, s16 arg1, s16 arg2) {
    void *temp_r3;

    temp_r3 = M2C_FIELD(arg0, void **, 0x440);
    if (temp_r3 != NULL) {
        M2C_FIELD(temp_r3, s16 *, 4) = arg1;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x440), s16 *, 6) = arg2;
    }
}
