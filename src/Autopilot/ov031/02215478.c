#include <m2c.h>

M2C_UNK ov00_021EA420();
s32 ov00_021EA580();
s32 ov00_021EA5C0();
void *ov00_021FAE14(M2C_UNK);
s32 ov00_021FAFC8(u8);

s32 ov00_021FCE7C(void *arg0) {
    s32 temp_r0;
    void *temp_r4;

    temp_r4 = ov00_021FAE14(1);
    temp_r0 = ov00_021EA580();
    if (temp_r0 != 0) {
        if (M2C_FIELD(temp_r4, u8 *, 0x15) == ov00_021FAFC8(M2C_FIELD(arg0, u8 *, 0xD0D))) {
            M2C_FIELD(temp_r4, s32 *, 0x10) = ov00_021EA5C0();
        }
        ov00_021EA420();
        if (temp_r0 == 0xB) {
            return 0xF;
        }
        M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0xD13) * 4)), s8 *, 0x444) = 1;
        return 0xB;
    }
    return 0xE;
}
