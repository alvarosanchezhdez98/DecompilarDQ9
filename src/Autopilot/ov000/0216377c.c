#include <m2c.h>

s32 func_020a1fa8();
s32 func_020a36a8(void *);
M2C_UNK func_ov026_021dbf04(void *);

void func_ov000_0216377c(void *arg0, s8 arg1) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x2A0);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s8 *, 0x2A) = arg1;
    if (func_020a36a8(M2C_FIELD(arg0, void **, 0x2A0)) != 0) {
        M2C_FIELD(arg0, s32 *, 0x55F4) = (s32) (M2C_FIELD(arg0, s32 *, 0x55F4) | 0x40000000);
    }
    if (func_020a1fa8() != 3) {
        return;
    }
    func_ov026_021dbf04(arg0);
}
