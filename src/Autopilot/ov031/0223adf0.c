#include <m2c.h>

M2C_UNK ov13_0223E5B4(M2C_UNK *);
M2C_UNK ov13_0223F3BC();
extern void *data_ov031_02290d20;
extern M2C_UNK ov13_0223F380;

void ov13_0223F130(void) {
    ov13_0223F3BC();
    ov13_0223E5B4(&ov13_0223F380);
    M2C_FIELD(data_ov031_02290d20, s8 *, 0xA90) = 8;
}
