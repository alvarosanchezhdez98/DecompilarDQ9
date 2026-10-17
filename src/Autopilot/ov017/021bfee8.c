#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
u32 _ZNK9GameState21GetEffectiveDeltaTimeEv();
M2C_UNK func_ov017_021bff2c();

s32 func_ov017_021bfee8(void *arg0) {
    u16 temp_r1;
    u32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZNK9GameState21GetEffectiveDeltaTimeEv();
    temp_r1 = M2C_FIELD(arg0, u16 *, 8);
    if (temp_r0 < (u32) temp_r1) {
        M2C_FIELD(arg0, u16 *, 8) = (u16) (temp_r1 - temp_r0);
        return 6;
    }
    M2C_FIELD(arg0, u16 *, 8) = 0U;
    func_ov017_021bff2c();
    return 8;
}
