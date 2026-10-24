#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_();

void func_020a0db8(void *arg0, s32 arg1, M2C_UNK arg2, s32 arg3) {
    _ZN8Vector3iaSERKS_(arg0 + 4);
    _ZN8Vector3iaSERKS_(arg0 + 0x10, arg2);
    M2C_FIELD(arg0, s32 *, 0x24) = arg3;
    M2C_FIELD(arg0, s32 *, 0) = 2;
}
