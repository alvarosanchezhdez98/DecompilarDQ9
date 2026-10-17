#include <m2c.h>

M2C_UNK ov00_021EB864();
s32 ov00_021EBB18();

s32 ov00_021ECCE0(void) {
    s32 temp_r0;

    temp_r0 = ov00_021EBB18();
    if ((u32) (temp_r0 - 3) <= 2U) {
        ov00_021EB864();
    }
    return temp_r0;
}
