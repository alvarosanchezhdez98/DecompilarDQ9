#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
u16 _ZNK6Script9Parameter5ToIntEv(s32);
s32 _ZNK6Script9Parameter7ToFloatEv(s32);
M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216a364(s32 arg0, s32 arg1) {
    s32 var_r4;
    u16 temp_r0_2;
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0x18);
    M2C_FIELD(temp_r0, s32 *, 0) = 0xC;
    M2C_FIELD(temp_r0, u16 *, 8) = _ZNK6Script9Parameter5ToIntEv(arg0);
    M2C_FIELD(temp_r0, s8 *, 0xA) = 0;
    M2C_FIELD(temp_r0, s32 *, 0xC) = 0;
    M2C_FIELD(temp_r0, s32 *, 0x10) = 0;
    M2C_FIELD(temp_r0, s32 *, 0x14) = 0;
    temp_r0_2 = M2C_FIELD(temp_r0, u16 *, 8);
    var_r4 = arg0 + 8;
    if ((temp_r0_2 != 5) && (temp_r0_2 != 6)) {

    } else {
        M2C_FIELD(temp_r0, s32 *, 0x14) = 0x3FE66666;
    }
    if (arg1 >= 2) {
        M2C_FIELD(temp_r0, s8 *, 0xA) = (s8) _ZNK6Script9Parameter5ToIntEv(var_r4);
        var_r4 += 8;
    }
    if (arg1 >= 3) {
        M2C_FIELD(temp_r0, s32 *, 0xC) = _ZNK6Script9Parameter7ToFloatEv(var_r4);
        M2C_FIELD(temp_r0, s32 *, 0x10) = _ZNK6Script9Parameter7ToFloatEv(var_r4 + 8);
        M2C_FIELD(temp_r0, s32 *, 0x14) = _ZNK6Script9Parameter7ToFloatEv(var_r4 + 0x10);
    }
    func_ov000_02169b78(temp_r0);
    return 1;
}
