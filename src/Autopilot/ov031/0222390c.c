#include <m2c.h>

M2C_UNK ov13_02227924(M2C_UNK *, M2C_UNK *);
s32 ov13_0222B980();
s32 ov13_0224128C(M2C_UNK, M2C_UNK);
extern M2C_UNK LoadToMainBG1CharacterData;
extern M2C_UNK LoadToMainBG1ScreenData;
extern M2C_UNK data_ov031_0224b3c0;
extern M2C_UNK data_ov031_0224b410;
extern s32 data_ov031_02250bf4;

void ov13_02227D58(void) {
    s32 temp_r0;

    data_ov031_02250bf4 = ov13_0224128C(0xC0, 4);
    ov13_02227924(&data_ov031_0224b410, &LoadToMainBG1CharacterData);
    temp_r0 = ov13_0222B980();
    switch (temp_r0) {                              /* irregular */
    case 0:
        ov13_02227924(M2C_FIELD(&data_ov031_0224b3c0, M2C_UNK **, 0), &LoadToMainBG1ScreenData);
        return;
    case 1:
        ov13_02227924(M2C_FIELD(&data_ov031_0224b3c0, M2C_UNK **, 4), &LoadToMainBG1ScreenData);
        return;
    }
}
