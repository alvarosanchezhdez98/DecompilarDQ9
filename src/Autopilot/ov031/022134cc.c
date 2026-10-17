#include <m2c.h>

void *ov00_021FAE14(M2C_UNK);
s8 ov00_021FAECC();

void ov00_021FAEE8(s32 arg0) {
    void *temp_r0;

    temp_r0 = ov00_021FAE14(1);
    M2C_FIELD(temp_r0, s32 *, 0xC) = arg0;
    M2C_FIELD(temp_r0, s8 *, 0xA) = ov00_021FAECC();
}
