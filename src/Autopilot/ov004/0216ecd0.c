#include <m2c.h>

void *_ZN9GameState11GetInstanceEv();
M2C_UNK func_02012010(void *, M2C_UNK);
s32 func_02012fe4();
M2C_UNK func_0201e828(s32, u16);
M2C_UNK func_0203b4a0(s32, s32);
M2C_UNK func_0203b4b0(s32, M2C_UNK);
M2C_UNK func_0203b4d8(s32, s32);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_0203b510(s32, s32);
M2C_UNK func_0203b520(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0218d258(s32);
extern M2C_UNK data_ov004_02171048;

s32 func_ov004_0216ecd0(void) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    void *temp_r5;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r0 = func_ov017_0218b5b0();
    func_0203b4b0(temp_r0, -1);
    func_0203b4e8(temp_r0, -1);
    func_0203b520(temp_r0, -1);
    func_0203b4a0(temp_r0, M2C_FIELD(M2C_FIELD(&data_ov004_02171048, void **, 4), s32 *, 0));
    func_0203b4d8(temp_r0, M2C_FIELD(M2C_FIELD(&data_ov004_02171048, void **, 4), s32 *, 4));
    func_0203b510(temp_r0, M2C_FIELD(M2C_FIELD(&data_ov004_02171048, void **, 4), s32 *, 8));
    temp_r0_2 = func_02012fe4();
    if (temp_r0_2 == 0) {
        return 0;
    }
    temp_r0_3 = temp_r0_2 + 0x6C;
    if (temp_r0_3 == 0) {
        return 0;
    }
    func_0201e828(temp_r0_3, M2C_FIELD(M2C_FIELD(&data_ov004_02171048, void **, 4), u16 *, 0xC));
    func_02012010(temp_r5, 5);
    M2C_FIELD(temp_r5, s8 *, 0x7F72) = 1;
    M2C_FIELD(temp_r5, s8 *, 0x7F73) = 1;
    func_ov017_0218d258(temp_r0);
    return 0;
}
