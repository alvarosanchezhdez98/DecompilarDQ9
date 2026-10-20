#include <m2c.h>

M2C_UNK func_02033b68(void *, M2C_UNK);
M2C_UNK func_0207964c(void *);

void func_0207872c(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xBE) != 2) {
        func_02033b68(arg0, 2);
    }
    func_0207964c(arg0);
}
