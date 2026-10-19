#include <m2c.h>

M2C_UNK func_ov031_0223e2b8(M2C_UNK, M2C_UNK *);
extern void *data_ov031_02250ba8;
extern M2C_UNK ov13_0222744C;

void ov13_022273FC(M2C_UNK arg0) {
    M2C_FIELD(data_ov031_02250ba8, s8 *, 0x16) = -1;
    M2C_FIELD(data_ov031_02250ba8, u16 *, 0x14) = (u16) (M2C_FIELD(data_ov031_02250ba8, u16 *, 0x14) + 1);
    if ((u32) M2C_FIELD(data_ov031_02250ba8, u16 *, 0x14) < 4U) {
        return;
    }
    M2C_FIELD(data_ov031_02250ba8, u16 *, 0x14) = 0U;
    func_ov031_0223e2b8(arg0, &ov13_0222744C);
}
