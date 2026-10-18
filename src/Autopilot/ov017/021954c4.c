#include <m2c.h>


void func_ov017_021954c4(void *arg0, s32 arg1) {
    void *temp_r3;
    void *temp_r3_2;

    temp_r3 = M2C_FIELD(arg0, void **, 0x441C);
    if ((M2C_FIELD(temp_r3, u8 *, 0) != 0) && (M2C_FIELD(temp_r3, u8 *, 2) == arg1)) {
        M2C_FIELD(temp_r3, u8 *, 0) = 0U;
        M2C_FIELD(temp_r3, s8 *, 1) = 0;
        temp_r3_2 = M2C_FIELD(arg0, void **, 0x3B30);
        if (M2C_FIELD(temp_r3_2, u8 *, 3) != 0) {
            M2C_FIELD(temp_r3_2, s8 *, 8) = 1;
        }
    }
    M2C_FIELD(arg0, u8 *, 0x431E) = (u8) (M2C_FIELD(arg0, u8 *, 0x431E) | (1 << arg1));
}
