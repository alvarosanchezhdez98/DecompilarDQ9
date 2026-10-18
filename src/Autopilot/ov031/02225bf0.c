#include <m2c.h>

M2C_UNK func_ov031_0223e2b8(s32, M2C_UNK *);
M2C_UNK ov13_0223FD60(s32);
extern void *data_ov031_02250c00;
extern M2C_UNK ov13_0222AF5C;

void ov13_0222A03C(void) {
    ov13_0223FD60(M2C_FIELD(data_ov031_02250c00, s32 *, 0x58));
    func_ov031_0223e2b8(M2C_FIELD(data_ov031_02250c00, s32 *, 0x5C), &ov13_0222AF5C);
}
