#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_0200fd48(s32, s32);
s32 func_0203cf4c();
void *func_0203df78(s32, s32);
s32 func_ov017_021d60f4(s32);
s32 func_ov001_0215ad2c();

s32 func_ov001_02160d14(s32 arg0) {
    s32 temp_r0;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    void *temp_r0_2;
    void *temp_r3;

    temp_r7 = _ZN9GameState11GetInstanceEv();
    temp_r6 = func_0203cf4c();
    temp_r5 = func_ov017_021d60f4(arg0);
    func_ov017_021d60f4(arg0 + 8);
    temp_r0 = func_ov001_0215ad2c();
    if ((temp_r0 < 0xA0) || (temp_r0 > 0xBF)) {
        return 0;
    }
    temp_r0_2 = func_0203df78(temp_r6, temp_r5);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    temp_r3 = M2C_FIELD(temp_r0_2, void **, 0x18);
    if (temp_r3 == NULL) {
        return 0;
    }
    M2C_FIELD(temp_r3, u8 *, 0xD4) = (u8) (M2C_FIELD(temp_r3, u8 *, 0xD4) & ~1);
    func_0200fd48(temp_r7, temp_r0);
    return 1;
}
