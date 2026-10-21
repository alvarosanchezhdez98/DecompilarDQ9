#include <m2c.h>

void *func_0206db20();

void func_0206dd68(void **arg0) {
    void *temp_r0;
    void *temp_r1;
    void *temp_r1_2;
    void *temp_r2;

    temp_r0 = func_0206db20();
    if (temp_r0 == NULL) {
        return;
    }
    temp_r2 = M2C_FIELD(temp_r0, void **, 0x64);
    temp_r1 = M2C_FIELD(temp_r0, void **, 0x68);
    if (temp_r2 != NULL) {
        M2C_FIELD(temp_r2, void **, 0x68) = temp_r1;
    } else {
        *arg0 = temp_r1;
    }
    temp_r1_2 = M2C_FIELD(temp_r0, void **, 0x68);
    if (temp_r1_2 != NULL) {
        M2C_FIELD(temp_r1_2, void **, 0x64) = (void *) M2C_FIELD(temp_r0, void **, 0x64);
    }
}
