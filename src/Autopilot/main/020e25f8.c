#include <m2c.h>

M2C_UNK func_020e1cb8(s32);
M2C_UNK func_020e25cc(void *);

void func_020e25e8(void *arg0) {
    func_020e1cb8(M2C_FIELD(arg0, s32 *, 0x10));
    func_020e25cc(arg0);
}
