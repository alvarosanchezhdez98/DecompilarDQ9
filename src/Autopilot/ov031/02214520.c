#include <m2c.h>

M2C_UNK func_020ca3ec(M2C_UNK, void *, M2C_UNK);
void *ov00_021FAE14(M2C_UNK);
u8 ov00_021FC004(void *);
u8 ov00_021FC064(void *);
u8 ov00_021FC258();
s8 ov00_021FC2E8(void *);

u8 ov00_021FBF24(s32 arg0) {
    void *temp_r4;

    temp_r4 = ov00_021FAE14(0x10);
    switch (arg0) {                                 /* irregular */
    case 0:
        func_020ca3ec(0, temp_r4 + 0x300, 0x144);
        M2C_FIELD(temp_r4, u8 *, 0xD10) = ov00_021FC004(temp_r4);
        break;
    case 1:
        M2C_FIELD(temp_r4, u8 *, 0xD10) = ov00_021FC258();
        M2C_FIELD(temp_r4, s8 *, 0xD0F) = ov00_021FC2E8(temp_r4);
        break;
    case 2:
        func_020ca3ec(0, temp_r4 + 0x300, 0x144);
        M2C_FIELD(temp_r4, s8 *, 0xD0F) = 0;
        M2C_FIELD(temp_r4, u8 *, 0xD10) = ov00_021FC064(temp_r4);
        break;
    }
    return M2C_FIELD(temp_r4, u8 *, 0xD10);
}
