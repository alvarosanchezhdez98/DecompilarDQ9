#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_02114e30;

void func_02045740(void *arg0) {
    s32 temp_r0;
    s32 temp_r1;

    M2C_FIELD(arg0, s32 *, 0x958) = (s32) ((M2C_FIELD(arg0, s32 *, 0x958) + 1) & 0x1F);
    if (func_02012444(&data_02114e30, 0x40) != 0) {
        temp_r0 = M2C_FIELD(arg0, s32 *, 0x954) - 1;
        M2C_FIELD(arg0, s32 *, 0x954) = temp_r0;
        if (temp_r0 < 0) {
            M2C_FIELD(arg0, s32 *, 0x954) = (s32) (M2C_FIELD(arg0, s32 *, 0x9A4) - 1);
        }
        M2C_FIELD(arg0, s32 *, 0x994) = (s32) M2C_FIELD(arg0, s32 *, 0x954);
        M2C_FIELD(arg0, s32 *, 0x958) = 0;
        return;
    }
    if (func_02012444(&data_02114e30, 0x80) == 0) {
        return;
    }
    temp_r1 = M2C_FIELD(arg0, s32 *, 0x954) + 1;
    M2C_FIELD(arg0, s32 *, 0x954) = temp_r1;
    if (temp_r1 >= (s32) M2C_FIELD(arg0, s32 *, 0x9A4)) {
        M2C_FIELD(arg0, s32 *, 0x954) = 0;
    }
    M2C_FIELD(arg0, s32 *, 0x994) = (s32) M2C_FIELD(arg0, s32 *, 0x954);
    M2C_FIELD(arg0, s32 *, 0x958) = 0;
}
