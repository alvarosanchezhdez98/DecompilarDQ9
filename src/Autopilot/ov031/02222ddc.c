#include <m2c.h>

M2C_UNK func_ov031_0223e2b8(s32, M2C_UNK *);
extern void *data_ov031_02250ba8;
extern M2C_UNK ov13_022275D8;

void ov13_02227228(void) {
    M2C_FIELD(data_ov031_02250ba8, s8 *, 0x19) = 1;
    func_ov031_0223e2b8(M2C_FIELD(data_ov031_02250ba8, s32 *, 0xC), &ov13_022275D8);
}
