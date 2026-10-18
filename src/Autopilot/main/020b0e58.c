#include <m2c.h>

M2C_UNK func_020b27c8(M2C_UNK, void *);
extern M2C_UNK func_020b2a58;

void func_020b0e48(void *arg0, M2C_UNK arg1) {
    func_020b27c8(arg1, arg0);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &func_020b2a58;
}
