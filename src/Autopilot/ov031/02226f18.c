#include <m2c.h>

M2C_UNK func_ov031_0221e894();
M2C_UNK ov13_0223A6E4(void *);
M2C_UNK ov13_022412B0(M2C_UNK *);
extern M2C_UNK data_ov031_02250c04;
extern M2C_UNK data_ov031_02250c08;

void func_ov031_02226f18(s32 arg0) {
    func_ov031_0221e894();
    if (arg0 != 0) {
        if ((M2C_FIELD(M2C_FIELD(&data_ov031_02250c04, void **, 4), u8 *, 0x116) == 0) && (M2C_FIELD(&data_ov031_02250c04, u8 *, 0) == 1)) {
            ov13_0223A6E4(M2C_FIELD(&data_ov031_02250c04, void **, 4) + 0x117);
        }
    }
    ov13_022412B0(&data_ov031_02250c08);
}
