#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_0200fb8c(s32);
s32 func_020100bc();
M2C_UNK func_ov000_02160130();
M2C_UNK func_ov000_0216d370(s32, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 data_ov025_021ef9a4;
extern s32 data_ov025_021ef9c0;

void func_ov025_021e9a94(void *arg0) {
    s32 temp_r4;
    s32 temp_r6;

    temp_r6 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_020100bc();
    func_0200fb8c(temp_r6);
    func_ov000_02160130();
    if (data_ov025_021ef9a4 & 1) {
        data_ov025_021ef9a4 = (data_ov025_021ef9a4 | 8) & ~1;
    }
    if (!(data_ov025_021ef9a4 & 2)) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C0) == 0) {
        func_ov000_0216d370(temp_r4, 1, 1, 1);
    }
    data_ov025_021ef9c0 += 1;
    data_ov025_021ef9a4 &= ~2;
}
