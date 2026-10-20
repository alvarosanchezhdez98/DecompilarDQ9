#include <m2c.h>

M2C_UNK func_020e1cdc(s32, M2C_UNK);
M2C_UNK func_020e25cc();
M2C_UNK func_020e2604(void *);

void func_020e280c(void *arg0, M2C_UNK arg1) {
    func_020e25cc();
    func_020e1cdc(M2C_FIELD(arg0, s32 *, 0x10), arg1);
    func_020e2604(arg0);
}
