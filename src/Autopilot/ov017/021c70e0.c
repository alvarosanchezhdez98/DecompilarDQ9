#include <m2c.h>

void *_ZN9GameState19GetCombatantByIndexEi(M2C_UNK, u16);
s32 func_020100a8(M2C_UNK);
M2C_UNK memcpy(s32, void *, M2C_UNK);
s32 func_ov017_021b8468(s32);
s32 func_ov017_021b8470(s32);
void *func_ov017_021b8478(s32);

void func_ov017_021c70e0(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3) {
    s32 temp_r6;
    void *temp_r0;
    void *temp_r0_2;

    temp_r6 = M2C_FIELD(arg3, s32 *, 0x3718);
    temp_r0 = func_ov017_021b8478(temp_r6);
    if (temp_r0 == NULL) {
        return;
    }
    if (func_ov017_021b8468(temp_r6) == 0) {
        return;
    }
    if (func_ov017_021b8470(temp_r6) == 0) {
        return;
    }
    if (M2C_FIELD(temp_r0, s8 *, 0x2A) == func_020100a8(arg2)) {
        return;
    }
    if (M2C_FIELD(temp_r0, u16 *, 8) != M2C_FIELD(arg1, u16 *, 4)) {
        return;
    }
    temp_r0_2 = _ZN9GameState19GetCombatantByIndexEi(arg2, M2C_FIELD(arg1, u16 *, 6));
    if (temp_r0_2 == NULL) {
        return;
    }
    memcpy(M2C_FIELD(temp_r0_2, void **, 0x138) + 0x58, arg1 + 8, 4);
    M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x138), s16 *, 0x28) = (s16) M2C_FIELD(arg1, s16 *, 0xC);
    M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x138), s16 *, 0x2A) = (s16) M2C_FIELD(arg1, s16 *, 0xE);
    M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x138), s16 *, 0x2C) = (s16) M2C_FIELD(arg1, s16 *, 0x10);
    M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x138), s16 *, 0x2E) = (s16) M2C_FIELD(arg1, s16 *, 0x12);
}
