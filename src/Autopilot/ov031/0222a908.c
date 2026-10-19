#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02237eb0();
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290c78;
extern M2C_UNK ov13_0222ED5C;

void ov13_0222ED00(void) {
    if (func_ov031_02237eb0() != 0) {
        return;
    }
    if (M2C_FIELD(&data_ov031_02290c78, u8 *, 1) == 0) {
        ov13_022403B8(3, 1, 1, 8);
    }
    ov13_022403B8(3, 0, 0x15, 8);
    func_ov031_022274c0(&ov13_0222ED5C);
}
