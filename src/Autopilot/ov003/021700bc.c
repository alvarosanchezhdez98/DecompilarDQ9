#include <m2c.h>

s32 func_02012fe4();
M2C_UNK func_ov003_0216ffbc(void *);

void func_ov003_021700bc(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x170) = (s32) (func_02012fe4() + 0x840);
    func_ov003_0216ffbc(arg0);
}
