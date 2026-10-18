#include <m2c.h>

void *func_ov001_02159eb0();

void *func_ov001_02159f14(void *arg0) {
    void *temp_r0;
    void *temp_r1;

    temp_r0 = func_ov001_02159eb0();
    if (temp_r0 == NULL) {
        return NULL;
    }
    temp_r1 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_r1 != NULL) {
        M2C_FIELD(temp_r1, void **, 0x3C) = temp_r0;
    }
    M2C_FIELD(arg0, void **, 0xC) = temp_r0;
    M2C_FIELD(temp_r0, s32 *, 0x3C) = 0;
    if (M2C_FIELD(arg0, void **, 8) == NULL) {
        M2C_FIELD(arg0, void **, 8) = temp_r0;
    }
    return temp_r0;
}
