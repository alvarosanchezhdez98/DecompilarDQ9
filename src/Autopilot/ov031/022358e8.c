#include <m2c.h>

M2C_UNK func_020d4848(void *);
s32 func_020d5004(M2C_UNK *);
s32 func_020d503c(M2C_UNK *);
extern void *data_ov031_02290cf8;
extern M2C_UNK ov13_02239D60;

s32 ov13_02239C68(void) {
    M2C_FIELD(data_ov031_02290cf8, s8 *, 0x1E5C) = 1;
    func_020d4848(data_ov031_02290cf8 + 0x168C);
    if (M2C_FIELD(data_ov031_02290cf8, u16 *, 0x168C) != 2) {
        if (func_020d5004(&ov13_02239D60) != 2) {
            return 0;
        }
        do {
            func_020d4848(data_ov031_02290cf8 + 0x168C);
        } while (M2C_FIELD(data_ov031_02290cf8, u16 *, 0x168C) != 2);
        goto block_5;
    }
block_5:
    if (func_020d503c(&ov13_02239D60) != 2) {
        return 0;
    }
    return 1;
}
