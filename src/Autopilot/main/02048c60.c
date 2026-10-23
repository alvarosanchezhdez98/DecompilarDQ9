#include <m2c.h>


void func_02048c50(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r1 != NULL) {
        M2C_FIELD(temp_r1, s32 *, 0x20) = (s32) (M2C_FIELD(temp_r1, s32 *, 0x20) & ~0x100);
    }
}
