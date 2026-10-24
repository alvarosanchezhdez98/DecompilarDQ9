#include <m2c.h>

void *_ZN9GameState19GetCombatantByIndexEi(M2C_UNK, u16);
s32 func_020100a8(M2C_UNK);
M2C_UNK func_02088818(void *, u8);
s32 func_ov017_021b8468(s32);
s32 func_ov017_021b8470(s32);
void *func_ov017_021b8478(s32);

void func_ov017_021c6ebc(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3) {
    s32 temp_r6;
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r2;
    void *temp_r2_2;
    void *temp_r2_3;

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
    temp_r2 = M2C_FIELD(temp_r0_2, void **, 0x138);
    M2C_FIELD(temp_r2, u16 *, 0x22) = (u16) ((M2C_FIELD(temp_r2, u16 *, 0x22) & ~3) | ((u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x1E) >> 0x1E) & 3));
    temp_r2_2 = M2C_FIELD(temp_r0_2, void **, 0x138);
    M2C_FIELD(temp_r2_2, u16 *, 0x22) = (u16) ((M2C_FIELD(temp_r2_2, u16 *, 0x22) & ~0x3C) | ((u32) ((u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x1A) >> 0x1C) << 0x1C) >> 0x1A));
    temp_r2_3 = M2C_FIELD(temp_r0_2, void **, 0x138);
    M2C_FIELD(temp_r2_3, u16 *, 0x22) = (u16) ((M2C_FIELD(temp_r2_3, u16 *, 0x22) & ~0x1C0) | ((u32) ((u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x17) >> 0x1D) << 0x1D) >> 0x17));
    func_02088818(M2C_FIELD(temp_r0_2, void **, 0x138), (u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x14) >> 0x1D));
    M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x138), u8 *, 0x24) = (u8) M2C_FIELD(arg1, u8 *, 0xA);
    M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x138), u16 *, 4) = (u16) M2C_FIELD(arg1, u16 *, 0xC);
    M2C_FIELD(M2C_FIELD(temp_r0_2, void **, 0x138), u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 0xE);
}
