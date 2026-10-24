#include <m2c.h>

s32 func_0202ae24();
M2C_UNK func_0205e330(s32, s8 *, M2C_UNK);
M2C_UNK func_ov017_021d2d00(M2C_UNK *, M2C_UNK);

void func_ov017_021d2cc0(M2C_UNK arg0) {
    M2C_UNK sp4[4];
    s8 sp0;
    s32 temp_r4;

    temp_r4 = func_0202ae24();
    sp0 = 0x25;
    func_ov017_021d2d00(sp4, arg0);
    func_0205e330(temp_r4, &sp0, 0);
}
