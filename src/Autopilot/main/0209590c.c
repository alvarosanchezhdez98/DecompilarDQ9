#include <m2c.h>


void func_020958fc(void *arg0, void *arg1) {
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0xA0);
    M2C_FIELD(arg0, void **, 0xA0) = arg1;
    if (temp_r2 != NULL) {
        M2C_FIELD(arg1, void **, 0xC) = temp_r2;
    }
}
