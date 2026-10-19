#include <m2c.h>

M2C_UNK func_ov031_0223e2b8(M2C_UNK, M2C_UNK *);
extern void *data_ov031_02290d10;
extern M2C_UNK ov13_0223C838;

void ov13_0223C7FC(M2C_UNK arg0) {
    M2C_FIELD(data_ov031_02290d10, u8 *, 0x1D) = (u8) (M2C_FIELD(data_ov031_02290d10, u8 *, 0x1D) + 1);
    if ((u32) M2C_FIELD(data_ov031_02290d10, u8 *, 0x1D) < 8U) {
        return;
    }
    func_ov031_0223e2b8(arg0, &ov13_0223C838);
}
