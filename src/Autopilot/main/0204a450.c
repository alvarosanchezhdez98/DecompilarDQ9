#include <m2c.h>

M2C_UNK func_0204a4ac(void *);
M2C_UNK strcpy(s32);

void func_0204a440(void *arg0) {
    strcpy(arg0 + 0x224);
    M2C_FIELD(arg0, s32 *, 0x254) = -1;
    func_0204a4ac(arg0);
}
