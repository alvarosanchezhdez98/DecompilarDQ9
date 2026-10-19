#include <m2c.h>


void func_02095910(void *arg0, void *arg1) {
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0xA4);
    M2C_FIELD(arg0, void **, 0xA4) = arg1;
    if (temp_r2 != NULL) {
        M2C_FIELD(arg1, void **, 0x28) = temp_r2;
    }
}
