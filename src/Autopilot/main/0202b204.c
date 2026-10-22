#include <m2c.h>

M2C_UNK _Z13SetBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
void *_ZN9GameState11GetInstanceEv();
M2C_UNK func_02011544(void *);
M2C_UNK func_020466e4(s32, M2C_UNK);
s32 func_02046708(s32, M2C_UNK);
s32 func_020d6c00();
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_021c37a4();
s32 func_0202b284(s32 *, M2C_UNK);

s32 func_0202b1f4(s32 *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r6;
    void *temp_r7;

    temp_r7 = _ZN9GameState11GetInstanceEv();
    temp_r6 = func_ov017_0218b5b0();
    temp_r0_2 = func_020d6c00();
    if (func_02046708(temp_r0_2, 0x01000000) != 0) {
        return 3;
    }
    temp_r0 = func_0202b284(arg0, 1);
    if ((u32) (u8) (temp_r0 + 0xFE) > 1U) {
        return temp_r0;
    }
    func_020466e4(temp_r0_2, 0x01000000);
    func_ov017_021c37a4();
    _Z13SetBrightnessP13GameResourcesii(temp_r6, -0x10, 0xA);
    M2C_FIELD(temp_r7, s8 *, 0x5CC8) = 4;
    func_02011544(temp_r7);
    *arg0 = 3;
    return 3;
}
