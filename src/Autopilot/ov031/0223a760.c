#include <m2c.h>

M2C_UNK ov13_0223CEA0();
extern void *data_ov031_02290d20;

s32 ov13_0223EAA0(void) {
    if (M2C_FIELD(data_ov031_02290d20, u8 *, 0xA90) != 5) {
        return 0;
    }
    M2C_FIELD(data_ov031_02290d20, u8 *, 0xA90) = 6U;
    ov13_0223CEA0();
    return 1;
}
