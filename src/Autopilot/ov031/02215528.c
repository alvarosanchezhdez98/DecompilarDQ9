#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(M2C_UNK *, void *, M2C_UNK);
s32 ov00_021FAFC8();
s32 ov00_021FCFEC(void *);
s32 ov00_021FD040(u8);
extern M2C_UNK data_ov031_02246028;

void ov00_021FCF2C(void *arg0, void *arg1, void *arg2) {
    void *temp_r5;

    VectorizedInvertedMemcpy(&data_ov031_02246028, arg2, 0x58);
    M2C_FIELD(arg2, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(arg2, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 4);
    if ((u32) M2C_FIELD(arg1, u8 *, 0xD0D) >= 6U) {
        return;
    }
    temp_r5 = arg1 + (ov00_021FAFC8() << 8);
    if (M2C_FIELD(temp_r5, u8 *, 0xC0) != 0) {
        M2C_FIELD(arg2, s32 *, 0xC) = 0;
        M2C_FIELD(arg2, s32 *, 0x10) = ov00_021FCFEC(temp_r5 + 0xC0);
        M2C_FIELD(arg2, s32 *, 0x14) = ov00_021FD040(M2C_FIELD(temp_r5, u8 *, 0xD0));
        M2C_FIELD(arg2, s32 *, 0x18) = ov00_021FCFEC(temp_r5 + 0xC4);
        M2C_FIELD(arg2, s32 *, 0x1C) = ov00_021FCFEC(temp_r5 + 0xC8);
        M2C_FIELD(arg2, s32 *, 0x20) = ov00_021FCFEC(temp_r5 + 0xCC);
        return;
    }
    M2C_FIELD(arg2, s32 *, 0xC) = 1;
    M2C_FIELD(arg2, s32 *, 0x10) = 0;
    M2C_FIELD(arg2, s32 *, 0x14) = 0;
    M2C_FIELD(arg2, s32 *, 0x18) = 0;
    M2C_FIELD(arg2, s32 *, 0x1C) = 0;
    M2C_FIELD(arg2, s32 *, 0x20) = 0;
}
