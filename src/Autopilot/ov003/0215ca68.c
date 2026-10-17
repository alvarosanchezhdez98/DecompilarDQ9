#include <m2c.h>

M2C_UNK func_0205d2bc(void *);
M2C_UNK func_ov003_0215db2c(void *);

void func_ov003_0215ca68(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x3BC) == 0) {
        return;
    }
    func_0205d2bc(arg0 + 0x98);
    func_ov003_0215db2c(arg0);
}
