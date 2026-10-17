#include <m2c.h>

M2C_UNK ov13_022402E0(s32);
extern s32 data_ov031_02290d60;

void ov13_02241D78(s32 arg0) {
    ov13_022402E0(M2C_FIELD((data_ov031_02290d60 + (arg0 * 4)), s32 *, 0x800));
}
