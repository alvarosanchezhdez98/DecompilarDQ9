#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState21GetEffectiveDeltaTimeEv();
M2C_UNK func_0202ae18();
M2C_UNK func_0202b0f4();
M2C_UNK func_ov003_02172518(void *, M2C_UNK);

void func_ov003_021716f8(void *arg0) {
    M2C_UNK var_r1;
    u32 temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x724) != 0) {
        if (((u32) M2C_FIELD(arg0, u32 *, 0x34C) >> 0x1F) != 0) {
            var_r1 = 1;
        } else {
            var_r1 = 0;
        }
        func_ov003_02172518(arg0, var_r1);
        M2C_FIELD(arg0, s8 *, 0) = 3;
    }
    _ZN9GameState11GetInstanceEv();
    temp_r0 = M2C_FIELD(arg0, u32 *, 0x72C) + _ZNK9GameState21GetEffectiveDeltaTimeEv();
    M2C_FIELD(arg0, u32 *, 0x72C) = temp_r0;
    if (temp_r0 <= 0xBB8U) {
        return;
    }
    func_0202ae18();
    func_0202b0f4();
    M2C_FIELD(arg0, s8 *, 0) = 4;
}
