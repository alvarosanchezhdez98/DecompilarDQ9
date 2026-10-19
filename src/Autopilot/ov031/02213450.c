#include <m2c.h>

void *ov00_021FAE14(M2C_UNK);
s8 ov00_021FAFC8(u8);

void ov00_021FAE6C(u8 arg0) {
    void *temp_r4;
    void *temp_r5;

    temp_r5 = ov00_021FAE14(1);
    temp_r4 = ov00_021FAE14(0x10);
    M2C_FIELD(temp_r5, u8 *, 9) = arg0;
    if ((u32) arg0 >= 0x10U) {
        return;
    }
    if ((u32) arg0 > (u32) M2C_FIELD(temp_r5, u8 *, 0x16)) {
        M2C_FIELD(temp_r5, u8 *, 0x16) = arg0;
        if ((u32) arg0 > 7U) {
            M2C_FIELD(temp_r5, s8 *, 0x15) = ov00_021FAFC8(M2C_FIELD(temp_r4, u8 *, 0xD0D));
            M2C_FIELD(temp_r5, u8 *, 0x14) = (u8) M2C_FIELD((temp_r4 + (M2C_FIELD(temp_r4, u8 *, 0xD13) * 4)), u8 *, 0x444);
        }
    }
}
