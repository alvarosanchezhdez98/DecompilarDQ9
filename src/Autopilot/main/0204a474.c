#include <m2c.h>

M2C_UNK func_0204a4ac(void *);
M2C_UNK strcpy(s32);

void func_0204a464(void *arg0) {
    strcpy(arg0 + 0x234);
    M2C_FIELD(arg0, s32 *, 0x258) = -1;
    func_0204a4ac(arg0);
}
