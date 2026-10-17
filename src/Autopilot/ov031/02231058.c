#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02231080();
M2C_UNK func_ov031_02231084();
s32 func_ov031_02237eb0();
extern M2C_UNK ov13_02235458;

void ov13_02235428(void) {
    func_ov031_02231080();
    func_ov031_02231084();
    if (func_ov031_02237eb0() != 0) {
        return;
    }
    func_ov031_022274c0(&ov13_02235458);
}
