#include <m2c.h>

M2C_UNK func_0205bbcc(s32);
M2C_UNK func_0205bef8(s32);

void func_0205c53c(void *arg0) {
    func_0205bbcc(arg0 + 4);
    func_0205bef8(arg0 + 0x54);
    M2C_FIELD(arg0, s8 *, 0x94) = 0;
    M2C_FIELD(arg0, s8 *, 0x95) = 0;
}
