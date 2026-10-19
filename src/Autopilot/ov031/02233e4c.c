#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02233e7c();
M2C_UNK ov13_022279EC(M2C_UNK);
extern s8 data_ov031_02290cd8;
extern M2C_UNK func_ov031_02233ee8;

void ov13_022381CC(void) {
    data_ov031_02290cd8 = 0;
    func_ov031_02233e7c();
    ov13_022279EC(0x2D);
    func_ov031_022274c0(&func_ov031_02233ee8);
}
