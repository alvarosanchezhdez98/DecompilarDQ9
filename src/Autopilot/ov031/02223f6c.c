#include <m2c.h>

M2C_UNK func_ov031_0223e2b8(s32, M2C_UNK *);
M2C_UNK ov13_0223FD60(s32);
extern void *data_ov031_02250bfc;
extern M2C_UNK ov13_022299CC;

void ov13_022283B8(void) {
    ov13_0223FD60(M2C_FIELD(data_ov031_02250bfc, s32 *, 0x114));
    func_ov031_0223e2b8(M2C_FIELD(data_ov031_02250bfc, s32 *, 0x118), &ov13_022299CC);
}
