#include <m2c.h>


void func_0206eeec(void *arg0, void *arg1) {
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 0);
    if (temp_r2 != NULL) {
        M2C_FIELD(arg1, void **, 0x10) = temp_r2;
        M2C_FIELD(arg0, void **, 0) = arg1;
    } else {
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg1, void **, 0x10) = NULL;
    }
    M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) + 1);
}
