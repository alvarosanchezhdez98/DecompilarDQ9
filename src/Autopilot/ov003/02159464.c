#include <m2c.h>

s32 func_02094a00();
M2C_UNK func_02094b30(s32, M2C_UNK, M2C_UNK);
s32 func_02094b4c();

void func_ov003_02159464(void *arg0) {
    s32 temp_r0;
    u8 temp_r1;

    if (M2C_FIELD(arg0, u8 *, 0x59D) == 0) {
        return;
    }
    temp_r0 = func_02094a00();
    temp_r1 = M2C_FIELD(arg0, u8 *, 0x59E);
    if (temp_r1 == 0) {
        func_02094b30(temp_r0, 0x200, 1);
        M2C_FIELD(arg0, u8 *, 0x59E) = (u8) (M2C_FIELD(arg0, u8 *, 0x59E) + 1);
        return;
    }
    if (temp_r1 != 1) {
        return;
    }
    if (func_02094b4c() != 0) {
        M2C_FIELD(arg0, u8 *, 0x59D) = 0U;
        M2C_FIELD(arg0, u8 *, 0x59E) = 0U;
    }
}
