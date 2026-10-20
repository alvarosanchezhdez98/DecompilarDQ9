#include <m2c.h>

M2C_UNK FastIntDivide(s32, u16);
s32 FastIntModulus(u16, M2C_UNK);
M2C_UNK func_ov031_022351f8();
M2C_UNK ov13_02227D18();
M2C_UNK ov13_022307AC();
M2C_UNK ov13_02230A58();
M2C_UNK ov13_02230CC4();
M2C_UNK ov13_02239584();
M2C_UNK ov13_0223959C();
M2C_UNK ov13_022425D0(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290c8c;

void ov13_02230BD0(M2C_UNK arg0) {
    s32 temp_r0;

    ov13_0223959C();
    ov13_02227D18();
    M2C_FIELD(&data_ov031_02290c8c, u16 *, 2) = (u16) (M2C_FIELD(&data_ov031_02290c8c, u16 *, 2) + 4);
    temp_r0 = FastIntModulus(M2C_FIELD(&data_ov031_02290c8c, u16 *, 2), 0x1C);
    if (temp_r0 >= 4) {
        ov13_02230A58();
        return;
    }
    M2C_FIELD(&data_ov031_02290c8c, u16 *, 2) = (u16) (M2C_FIELD(&data_ov031_02290c8c, u16 *, 2) - temp_r0);
    ov13_022307AC();
    FastIntDivide(M2C_FIELD(&data_ov031_02290c8c, u16 *, 2) * M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), u8 *, 0x53), M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), u16 *, 0x40));
    func_ov031_022351f8();
    ov13_02239584();
    ov13_02230CC4();
    M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), s32 *, 0x38) = 0;
    ov13_022425D0(0, arg0);
}
