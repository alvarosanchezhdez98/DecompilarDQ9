#include <m2c.h>

M2C_UNK func_020d0050(u16);
extern M2C_UNK data_02108dfc;

void func_02075cb8(void) {
    func_020d0050(M2C_FIELD(&data_02108dfc, u16 *, 2));
    M2C_FIELD(&data_02108dfc, s8 *, 0) = 1;
}
