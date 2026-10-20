#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02230ef0(M2C_UNK);
s32 ov13_022272A0();
M2C_UNK ov13_0222788C();
M2C_UNK ov13_02227924(M2C_UNK *, M2C_UNK *);
M2C_UNK ov13_02227D18();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
M2C_UNK ov13_0222B934(M2C_UNK, M2C_UNK);
void *ov13_02239FF0();
s32 ov13_0223B6C8();
M2C_UNK ov13_0223FA50(s32);
M2C_UNK ov13_0223FD60();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
M2C_UNK ov13_022412B0(M2C_UNK *);
extern M2C_UNK LoadToMainObjStandardPalette;
extern M2C_UNK data_ov031_0224bcec;
extern M2C_UNK data_ov031_02290cc0;
extern M2C_UNK data_ov031_02290cc4;
extern M2C_UNK ov13_0222C44C;
extern M2C_UNK ov13_02232E04;
extern M2C_UNK ov13_02237618;
extern M2C_UNK ov13_022388A0;

void ov13_02236F14(void) {
    u32 var_r5;
    u32 var_r5_2;

    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    if (ov13_0223B6C8() == 0) {
        return;
    }
    if (ov13_022272A0() == 0) {
        return;
    }
    var_r5 = 0;
    do {
        if (M2C_FIELD((M2C_FIELD(&data_ov031_02290cc0, void **, 4) + (var_r5 * 4)), s32 *, 4) != 0) {
            ov13_0223FD60();
        }
        var_r5 += 1;
    } while (var_r5 < 3U);
    var_r5_2 = 0;
    do {
        if (M2C_FIELD((M2C_FIELD(&data_ov031_02290cc0, void **, 4) + (var_r5_2 * 4)), s32 *, 0x10) != 0) {
            ov13_0223FD60();
        }
        var_r5_2 += 1;
    } while (var_r5_2 < 3U);
    ov13_02227D18();
    ov13_0222788C();
    ov13_0223FA50(M2C_FIELD(M2C_FIELD(&data_ov031_02290cc0, void **, 4), s32 *, 0));
    ov13_02227924(&data_ov031_0224bcec, &LoadToMainObjStandardPalette);
    ov13_02240EFC(1, 1);
    ov13_02240EFC(0, 0x14);
    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290cc0, void **, 4), u8 *, 0x1D) == 2) {
        ov13_0222B8F8(0, 0);
        func_ov031_022274c0(&ov13_0222C44C);
    } else {
        switch (M2C_FIELD(&data_ov031_02290cc0, u8 *, 0)) {
        default:
            break;
        case 0:
        case 1:
        case 2:
            ov13_0222B8F8(2, 0);
            if (M2C_FIELD(ov13_02239FF0(), u8 *, 0xE7) == 0xFF) {
                func_ov031_022274c0(&ov13_02237618);
            } else {
                ov13_0222B934(0, 0);
                func_ov031_02230ef0(0);
                func_ov031_022274c0(&ov13_02232E04);
            }
            break;
        case 3:
            ov13_0222B8F8(2, 1);
            func_ov031_022274c0(&ov13_022388A0);
            break;
        }
    }
    ov13_022412B0(&data_ov031_02290cc4);
}
