#include <m2c.h>

M2C_UNK func_020c9be0();
s32 func_020d503c(M2C_UNK *);
M2C_UNK ov13_0223D6A8(M2C_UNK);
extern M2C_UNK data_ov031_02290d18;
extern M2C_UNK ov13_0223DED8;

s32 ov13_0223E7BC(void) {
    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x40) != 1) {
        func_020c9be0();
    }
    ov13_0223D6A8(3);
    if (func_020d503c(&ov13_0223DED8) == 2) {
        return 1;
    }
    ov13_0223D6A8(9);
    return 0;
}
