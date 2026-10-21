#include <m2c.h>


void func_020469f8(void *arg0, void *arg1) {
    void *temp_r3;

    temp_r3 = M2C_FIELD(arg0, void **, 0);
    if ((temp_r3 != NULL) && (M2C_FIELD(arg0, void **, 4) != NULL)) {
        M2C_FIELD(temp_r3, s8 *, 3) = 0;
        M2C_FIELD(arg1, void **, 4) = (void *) M2C_FIELD(arg0, void **, 0);
        M2C_FIELD(arg0, void **, 0) = arg1;
    } else {
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg0, void **, 4) = arg1;
        M2C_FIELD(arg1, void **, 4) = NULL;
    }
    M2C_FIELD(arg1, s8 *, 2) = 1;
}
