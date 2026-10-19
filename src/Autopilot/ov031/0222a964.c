#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02227874();
M2C_UNK ov13_0222BC0C();
s32 ov13_02240394(M2C_UNK);
extern M2C_UNK data_ov031_02290c78;
extern M2C_UNK ov13_0222EDB8;

void ov13_0222ED5C(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    if ((M2C_FIELD(&data_ov031_02290c78, u8 *, 0) == 0) && (M2C_FIELD(&data_ov031_02290c78, u8 *, 1) == 1)) {
        func_ov031_02227874();
    } else {
        ov13_0222BC0C();
    }
    func_ov031_022274c0(&ov13_0222EDB8);
}
