#include <m2c.h>

M2C_UNK func_ov017_021bb27c(void *);
M2C_UNK func_ov001_02154da0();

u16 func_ov001_02156534(void *arg0) {
    func_ov001_02154da0();
    func_ov017_021bb27c(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
    return M2C_FIELD(arg0, u16 *, 0xA);
}
