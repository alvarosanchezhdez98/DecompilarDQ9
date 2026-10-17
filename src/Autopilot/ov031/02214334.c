#include <m2c.h>

s32 ov00_021FAE14(M2C_UNK);
s32 ov00_021FBBF0(s32);

s32 ov00_021FBD38(void) {
    if (ov00_021FBBF0(ov00_021FAE14(1) + 0xA) == 1) {
        return 0x12;
    }
    return 0x11;
}
