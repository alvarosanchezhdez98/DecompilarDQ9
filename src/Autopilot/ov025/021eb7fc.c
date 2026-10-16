#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, u16);
M2C_UNK func_02033874(void *, s16);
M2C_UNK func_02033920(void *, s16, M2C_UNK);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
void *func_ov000_02160094(s32, M2C_UNK);
void *func_ov000_021600f8(s32, M2C_UNK);
s32 func_ov000_02160130();
void *func_ov000_02160f14();
s32 func_ov000_02160f20(s32);
M2C_UNK func_ov000_02163710(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov025_021eb00c(void *);
M2C_UNK func_ov025_021eb8e8(void *);

void func_ov025_021eb7fc(void *arg0) {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r7;
    s32 temp_r8;
    void *temp_r0_2;
    void *temp_r5;
    void *temp_r7_2;
    void *temp_r8_2;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r8 = func_ov017_0218b5b0();
    temp_r7 = func_ov000_02160130();
    temp_r5 = func_ov000_02160f14();
    M2C_FIELD(temp_r5, s32 *, 0x27C) = func_ov000_02160f20(temp_r7);
    func_ov025_021eb00c(arg0);
    func_ov000_02163710(temp_r7, 0);
    func_ov025_021eb8e8(arg0);
    if (!(M2C_FIELD(arg0, s32 *, 0x1C4) & 0x20)) {
        func_0203b4e8(temp_r8, 0x400);
        if (M2C_FIELD(arg0, s32 *, 0x1C4) & 0x80) {
            temp_r0 = func_ov000_02160f20(temp_r7);
            temp_r8_2 = func_ov000_02160094(temp_r0, 0);
            temp_r7_2 = func_ov000_021600f8(temp_r0, 0);
            if ((temp_r8_2 != NULL) && (temp_r7_2 != NULL)) {
                temp_r0_2 = _ZN9GameState19GetCombatantByIndexEi(temp_r4, M2C_FIELD(temp_r8_2, u16 *, 0x20));
                if (temp_r0_2 != NULL) {
                    func_02033920(temp_r0_2, M2C_FIELD(temp_r7_2, s16 *, 0xE), 0);
                    func_02033874(temp_r0_2, M2C_FIELD(temp_r0_2, s16 *, 0xAE));
                }
            }
        }
        M2C_FIELD(temp_r5, s8 *, 0x278) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x1C4) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C4) | 0x20);
}
