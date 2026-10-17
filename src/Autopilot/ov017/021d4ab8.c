#include <m2c.h>


void func_ov017_021d4ab8(void *arg0, s32 arg1) {
    void *temp_r3;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), s32 *, 0) = 3;
    temp_r3 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(arg0, void **, 0x14) = (void *) (temp_r3 + 8);
    M2C_FIELD(temp_r3, s32 *, 4) = arg1;
}
