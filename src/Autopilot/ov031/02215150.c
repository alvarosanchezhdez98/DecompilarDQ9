#include <m2c.h>

s32 ov00_021FBF24(M2C_UNK);
s8 ov00_021FC500(M2C_UNK);
s32 ov00_021FC73C(void *);

s32 ov00_021FCB54(void *arg0) {
    if ((M2C_FIELD(arg0, u16 *, 0xD16) != 0) && (ov00_021FBF24(2) != 0)) {
        M2C_FIELD(arg0, s8 *, 0xD11) = ov00_021FC500(0);
        return 5;
    }
    if ((u32) ((u32) (M2C_FIELD(arg0, u8 *, 0xD0B) << 0x18) >> 0x1C) >= 1U) {
        return 6;
    }
    return ov00_021FC73C(arg0);
}
