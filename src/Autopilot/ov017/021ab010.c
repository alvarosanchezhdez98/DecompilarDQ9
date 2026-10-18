#include <m2c.h>

M2C_UNK func_0209c2e0(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_0209c5e8(M2C_UNK *);
s32 func_0209c6bc(M2C_UNK *);
M2C_UNK func_ov017_021aaf08();
extern M2C_UNK data_02109bf4;

void func_ov017_021ab010(void *arg0, s32 arg1) {
    func_ov017_021aaf08();
    if ((arg1 != 0) && (func_0209c6bc(&data_02109bf4) == 0)) {
        func_0209c5e8(&data_02109bf4);
        func_0209c2e0(&data_02109bf4, 0x7F, 0);
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
