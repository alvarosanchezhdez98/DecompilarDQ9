#include <m2c.h>

u16 *func_02012fe4();
M2C_UNK func_02015a98(s32, u8, M2C_UNK, M2C_UNK);
s32 func_020177a8(u16 *, u16);

void func_ov017_021cfda0(s32 arg0, void *arg1) {
    s32 temp_r0_2;
    u16 *temp_r0;

    temp_r0 = func_02012fe4();
    if (M2C_FIELD(arg1, u16 *, 4) != *temp_r0) {
        return;
    }
    temp_r0_2 = func_020177a8(temp_r0, M2C_FIELD(arg1, u16 *, 6));
    if (temp_r0_2 == 0) {
        return;
    }
    func_02015a98(temp_r0_2, M2C_FIELD(arg1, u8 *, 8), 0, 0);
}
