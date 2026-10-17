#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_02011af0(s32);
M2C_UNK func_02011b50(s32, M2C_UNK);
s32 func_0205ec34();
M2C_UNK func_0206df6c(s32, s32, M2C_UNK, M2C_UNK);

s32 func_ov004_02168884(void) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    func_02011b50(temp_r0, 1);
    func_02011af0(temp_r0);
    temp_r0_2 = func_0205ec34();
    func_0206df6c(temp_r0_2, temp_r0_2 + 0x8C, 3, 0);
    return 0;
}
