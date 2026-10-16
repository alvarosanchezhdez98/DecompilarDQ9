#include <m2c.h>

void *_Z16GetCombatantByIDii(s32);
s32 func_020882f8(void *);
s32 func_02088514(void *);
s32 func_020885b4(void *);
s32 func_ov024_021da9b0(void *);
s32 func_ov024_021da9c8(void *);
s32 func_ov024_021dd010(void *);
s32 func_ov024_021de25c(void *);
s32 func_ov024_021df6ec(void *);

s32 func_ov024_021edcc8(s32 *arg0) {
    s32 temp_r0_2;
    void *temp_r0;

    temp_r0 = _Z16GetCombatantByIDii(*arg0);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (func_020882f8(M2C_FIELD(temp_r0, void **, 0x138)) != 0) {
        return 1;
    }
    if (func_ov024_021de25c(temp_r0) != 0) {
        return 1;
    }
    if (func_ov024_021da9b0(temp_r0) != 0) {
        return 1;
    }
    if (func_ov024_021da9c8(temp_r0) != 0) {
        return 1;
    }
    if (func_020885b4(M2C_FIELD(temp_r0, void **, 0x138)) != 0) {
        return 1;
    }
    if (func_02088514(M2C_FIELD(temp_r0, void **, 0x138)) != 0) {
        return 1;
    }
    if (func_ov024_021df6ec(temp_r0) != 0) {
        return 1;
    }
    if (func_ov024_021dd010(temp_r0) != 0) {
        return 1;
    }
    temp_r0_2 = M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), s32 *, 0x58);
    if ((s32) ((s32) (temp_r0_2 << 0x1D) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 0x1A) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 0x17) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 0x14) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 0x11) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 0xE) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 0xB) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 8) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 * 4) >> 0x1D) < 0) {
        return 1;
    }
    if ((s32) ((s32) (temp_r0_2 << 5) >> 0x1D) < 0) {
        return 1;
    }
    return 0;
}
