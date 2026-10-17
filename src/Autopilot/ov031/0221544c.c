#include <m2c.h>

s32 ov00_021EA340();
M2C_UNK ov00_021FAE14(M2C_UNK);
M2C_UNK ov00_021FAEE8(M2C_UNK);

s32 ov00_021FCE50(void) {
    ov00_021FAE14(8);
    if (ov00_021EA340() == 0) {
        return 0xE;
    }
    ov00_021FAEE8(3);
    return 0x11;
}
