#include <m2c.h>

M2C_UNK func_ov003_02158d4c();
M2C_UNK func_ov017_021ba94c(void *);

void func_ov017_021babf8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x1C) != 0) {
        func_ov003_02158d4c();
    }
    func_ov017_021ba94c(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
