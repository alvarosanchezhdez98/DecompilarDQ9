#include <m2c.h>

M2C_UNK func_ov003_0215c800();
M2C_UNK func_ov017_021bac8c(void *);

void func_ov017_021baeb0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x20) != 0) {
        func_ov003_0215c800();
    }
    func_ov017_021bac8c(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
