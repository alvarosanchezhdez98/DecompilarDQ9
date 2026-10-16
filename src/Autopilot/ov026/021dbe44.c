#include <m2c.h>

s32 func_02046b08(s32);
s32 func_020a35e0(void *, u8);
void *func_ov017_0218b5b0();
s32 func_ov026_021d8a40();
M2C_UNK func_ov026_021dce34(M2C_UNK, void *, s32, void *, void *, void *, void *, void *, void *, void *, void *, void *);

void func_ov026_021dbe44(void *arg0) {
    s32 temp_r5;
    void *temp_r0;

    temp_r5 = M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x3704);
    if ((func_ov026_021d8a40() != 0) && (func_02046b08(temp_r5) != 0)) {
        temp_r0 = M2C_FIELD(arg0, void **, 0x2A0);
        if (func_020a35e0(temp_r0, M2C_FIELD(temp_r0, u8 *, 0x2A)) != 0) {
            func_ov026_021dce34(-1, arg0, M2C_FIELD(arg0, s32 *, 0x29C), M2C_FIELD(arg0, void **, 0x2A0), arg0 + 0x3760, arg0 + 0xEC8, arg0 + 0x5C3C, arg0 + 0x5728, arg0 + 0xE98, arg0 + 0xEA0, arg0 + 0x5910, arg0 + 0xC18);
        }
    }
}
