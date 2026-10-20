#include <m2c.h>

M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, s32);
M2C_UNK memcpy(s32, s32, M2C_UNK);

void func_0204ad88(void *arg0, s32 arg1) {
    memcpy(arg0 + 8, arg1 + 0xC, 4);
    _Z25CleanInvalidateCacheRangePKvj(arg1 + 0x10, M2C_FIELD(arg0, s32 *, 8));
}
