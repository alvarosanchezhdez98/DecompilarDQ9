#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02237eb0();
extern void *data_ov031_02290c98;
extern M2C_UNK ov13_02231D9C;

void func_ov031_0222e3a4(void) {
    s32 *temp_r3;

    if (func_ov031_02237eb0() != 0) {
        return;
    }
    temp_r3 = M2C_FIELD(data_ov031_02290c98, s32 **, 4);
    *temp_r3 &= 0xC1FFFCFF;
    func_ov031_022274c0(&ov13_02231D9C);
}
