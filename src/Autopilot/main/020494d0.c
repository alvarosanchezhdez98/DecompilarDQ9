#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_02033920(void *, u8, M2C_UNK);

void func_020494c0(void *arg0) {
    u8 var_r1;
    void *temp_r0;

    if (M2C_FIELD(arg0, void **, 0x13C) == NULL) {
        return;
    }
    _ZN9GameState11GetInstanceEv();
    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    var_r1 = M2C_FIELD(temp_r0, u8 *, 0x4C);
    if (var_r1 == 0xFF) {
        var_r1 = M2C_FIELD(temp_r0, u8 *, 0x4D);
    }
    func_02033920(arg0, var_r1, 0);
}
