#include <m2c.h>

s32 func_020100a8(M2C_UNK);
M2C_UNK func_02088818(s32, u8);
void *func_ov017_021b8478(s32);

void func_ov017_021ca6dc(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3) {
    s32 temp_r2;
    s32 temp_r4;
    void *temp_r0;

    temp_r0 = func_ov017_021b8478(M2C_FIELD(arg3, s32 *, 0x3718));
    if (temp_r0 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r0, s8 *, 0x2A) == func_020100a8(arg2)) {
        return;
    }
    if (M2C_FIELD(temp_r0, u16 *, 8) != M2C_FIELD(arg1, u16 *, 4)) {
        return;
    }
    temp_r2 = M2C_FIELD(arg1, u16 *, 6) - 0xC0;
    if (temp_r2 < 0) {
        return;
    }
    if (temp_r2 >= 8) {
        return;
    }
    temp_r4 = (temp_r2 * 0xA4) + (s32) (temp_r0 + 0x158);
    M2C_FIELD(temp_r4, u16 *, 0x22) = (u16) ((M2C_FIELD(temp_r4, u16 *, 0x22) & ~3) | ((u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x1E) >> 0x1E) & 3));
    M2C_FIELD(temp_r4, u16 *, 0x22) = (u16) ((M2C_FIELD(temp_r4, u16 *, 0x22) & ~0x3C) | ((u32) ((u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x1A) >> 0x1C) << 0x1C) >> 0x1A));
    M2C_FIELD(temp_r4, u16 *, 0x22) = (u16) ((M2C_FIELD(temp_r4, u16 *, 0x22) & ~0x1C0) | ((u32) ((u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x17) >> 0x1D) << 0x1D) >> 0x17));
    func_02088818(temp_r4, (u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x14) >> 0x1D));
    M2C_FIELD(temp_r4, u16 *, 0x22) = (u16) ((M2C_FIELD(temp_r4, u16 *, 0x22) & ~0x3000) | ((u32) ((u8) ((u32) (M2C_FIELD(arg1, u16 *, 8) << 0x12) >> 0x1E) << 0x1E) >> 0x12));
    M2C_FIELD(temp_r4, u8 *, 0x24) = (u8) M2C_FIELD(arg1, u8 *, 0xA);
    M2C_FIELD(temp_r4, u8 *, 0x25) = (u8) M2C_FIELD(arg1, u8 *, 0xB);
    M2C_FIELD(temp_r4, u16 *, 4) = (u16) M2C_FIELD(arg1, u16 *, 0xC);
    M2C_FIELD(temp_r4, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 0xE);
    M2C_FIELD(temp_r4, u16 *, 8) = (u16) M2C_FIELD(arg1, u16 *, 0x10);
    M2C_FIELD(temp_r4, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0x12);
}
