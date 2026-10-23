#include <m2c.h>

M2C_UNK func_ov017_021d60f4();
M2C_UNK func_ov001_0215a3c0();
s32 func_ov001_0215ab20();

s32 func_ov001_0215c40c(void) {
    func_ov017_021d60f4();
    if (func_ov001_0215ab20() == 0) {
        return 0;
    }
    func_ov001_0215a3c0();
    return 1;
}
