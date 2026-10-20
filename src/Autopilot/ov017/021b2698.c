#include <m2c.h>

s32 _ZN10MenuScript6UpdateEv(s32);
s32 func_02012444(M2C_UNK *, M2C_UNK);
M2C_UNK func_0202ae18();
s32 func_0202c540();
s32 func_020936f8();
M2C_UNK func_02094030(s32, s32, M2C_UNK, M2C_UNK);
void *func_ov017_0218b5b0();
s32 func_ov017_0219bddc(s8 *);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_ov017_021d83f0;

s32 func_ov017_021b2698(void *arg0) {
    s8 sp0;

    if (func_02012444(&data_02114e30, 0x2000) != 0) {
        return 3;
    }
    if (_ZN10MenuScript6UpdateEv(M2C_FIELD(&data_ov017_021d83f0, s32 *, 4)) != 0) {
        return M2C_FIELD(arg0, s32 *, 8);
    }
    if (M2C_FIELD(M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3B3C), u8 *, 2) == 0) {
        func_0202ae18();
        if (func_0202c540() != 0) {
            sp0 = 0;
            if (func_ov017_0219bddc(&sp0) != 0) {
                M2C_FIELD(arg0, s32 *, 0x38) = (s32) ((M2C_FIELD(arg0, s32 *, 0x38) & ~1) | 1);
                M2C_FIELD(arg0, s8 *, 0x48) = 1;
                func_02094030(func_020936f8(), 0x4E23, -1, 0);
            }
        }
    }
    return 3;
}
