#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_02012fe4();
M2C_UNK func_0201e828(s32, u16);
M2C_UNK func_0203b4a0(void *, s32);
M2C_UNK func_0203b4b0(void *, M2C_UNK);
M2C_UNK func_0203b4d8(void *, s32);
M2C_UNK func_0203b4e8(void *, M2C_UNK);
M2C_UNK func_0203b510(void *, s32);
M2C_UNK func_0203b520(void *, M2C_UNK);
void *func_020421a0();
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021a967c(s32, M2C_UNK);
extern void *data_ov004_02171030;

s32 func_ov004_02169144(void) {
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r4;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_ov017_0218b5b0();
    temp_r4 = M2C_FIELD(temp_r0, s32 *, 0x3B84);
    func_0203b4b0(temp_r0, -1);
    func_0203b4e8(temp_r0, -1);
    func_0203b520(temp_r0, -1);
    func_0203b4a0(temp_r0, M2C_FIELD(data_ov004_02171030, s32 *, 0x180));
    func_0203b4d8(temp_r0, M2C_FIELD(data_ov004_02171030, s32 *, 0x184));
    func_0203b510(temp_r0, M2C_FIELD(data_ov004_02171030, s32 *, 0x188));
    temp_r0_2 = func_02012fe4();
    if (temp_r0_2 == 0) {
        return 0;
    }
    temp_r0_3 = temp_r0_2 + 0x6C;
    if (temp_r0_3 == 0) {
        return 0;
    }
    func_0201e828(temp_r0_3, M2C_FIELD(data_ov004_02171030, u16 *, 0x18C));
    func_ov017_021a967c(temp_r4, -1);
    M2C_FIELD(func_020421a0(), s8 *, 0x1962) = 0;
    return 0;
}
