#include <m2c.h>

s32 ov13_0223DF28();
M2C_UNK ov13_0223E7BC();
extern void *data_ov031_02290d20;

s32 ov13_0223F350(void) {
    if (ov13_0223DF28() != 1) {
        return 0;
    }
    ov13_0223E7BC();
    M2C_FIELD(data_ov031_02290d20, s8 *, 0xA90) = 1;
    return 1;
}
