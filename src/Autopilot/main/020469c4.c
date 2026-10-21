#include <m2c.h>


void func_020469b4(void *arg0, void *arg1) {
    void *temp_r2;

    if ((M2C_FIELD(arg0, void **, 0) != NULL) && (temp_r2 = M2C_FIELD(arg0, void **, 4), (temp_r2 != NULL))) {
        M2C_FIELD(temp_r2, void **, 4) = arg1;
        M2C_FIELD(arg0, void **, 4) = arg1;
        M2C_FIELD(arg1, s32 *, 4) = 0;
    } else {
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg0, void **, 4) = arg1;
        M2C_FIELD(arg1, s32 *, 4) = 0;
    }
    M2C_FIELD(arg1, s32 *, 4) = 0;
    M2C_FIELD(arg1, s8 *, 2) = 1;
}
