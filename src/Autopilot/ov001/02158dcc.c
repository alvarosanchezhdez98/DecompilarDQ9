#include <m2c.h>

void *func_ov001_02158d8c();

void *func_ov001_02158dcc(void *arg0) {
    void *temp_r0;
    void *temp_r1;

    temp_r0 = func_ov001_02158d8c();
    if (temp_r0 == NULL) {
        return NULL;
    }
    temp_r1 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_r1 != NULL) {
        M2C_FIELD(temp_r1, void **, 0x48) = temp_r0;
    }
    M2C_FIELD(arg0, void **, 0xC) = temp_r0;
    M2C_FIELD(temp_r0, s32 *, 0x48) = 0;
    if (M2C_FIELD(arg0, void **, 8) == NULL) {
        M2C_FIELD(arg0, void **, 8) = temp_r0;
    }
    return temp_r0;
}
