#include <m2c.h>

M2C_UNK func_0205d1e0(void *);
M2C_UNK func_0205d228(void *);
M2C_UNK func_0205d274(void *);
M2C_UNK func_0205da88(void *, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_ov003_0215e2a8(void *);

void func_ov003_0215ca1c(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x3BC) == 0) {
        return;
    }
    func_0205d1e0(arg0 + 0x98);
    func_0205d228(arg0 + 0x98);
    func_0205da88(arg0 + 0x98, 1, 2, 1);
    func_0205d274(arg0 + 0x98);
    func_ov003_0215e2a8(arg0);
}
