#include <m2c.h>

M2C_UNK func_0203fca0(s32);

void func_02040258(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    func_0203fca0(arg0 + 0x10);
    M2C_FIELD(arg0, s32 *, 0x38) = -1;
}
