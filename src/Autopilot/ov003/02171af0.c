#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState21GetEffectiveDeltaTimeEv(s32);
s32 func_0202ae18();
M2C_UNK func_0202b0f4(s32);
s32 func_0202c1a4(s32);
M2C_UNK func_0202c1e8(s32, s32);
M2C_UNK func_0202c288(s32);
M2C_UNK func_ov003_02172518(void *, M2C_UNK);

void func_ov003_02171af0(void *arg0) {
    M2C_UNK var_r1;
    s32 temp_r5;
    s32 temp_r6;
    u32 temp_r0;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r6 = func_0202ae18();
    temp_r0 = M2C_FIELD(arg0, u32 *, 0x72C) + _ZNK9GameState21GetEffectiveDeltaTimeEv(temp_r5);
    M2C_FIELD(arg0, u32 *, 0x72C) = temp_r0;
    if (temp_r0 > 0xBB8U) {
        func_0202b0f4(temp_r6);
        M2C_FIELD(arg0, u32 *, 0x72C) = 0U;
        M2C_FIELD(arg0, s8 *, 0) = 0;
    }
    if (func_0202c1a4(temp_r6) <= 0) {
        return;
    }
    func_0202c1e8(temp_r6, func_0202c1a4(temp_r6));
    func_0202c1e8(temp_r6, (s32) M2C_FIELD(arg0, u8 *, 0x199));
    func_0202c288(temp_r6);
    if (((u32) (M2C_FIELD(arg0, u8 *, 0x1B1) << 0x19) >> 0x1F) != 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov003_02172518(arg0, var_r1);
    M2C_FIELD(arg0, s8 *, 0) = 7;
}
