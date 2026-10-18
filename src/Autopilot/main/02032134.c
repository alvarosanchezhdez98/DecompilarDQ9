#include <m2c.h>

s32 Vector3fix_InnerProduct(void *, M2C_UNK);

s32 func_02032124(M2C_UNK arg0, void *arg1) {
    return Vector3fix_InnerProduct(arg1, arg0) - M2C_FIELD(arg1, s32 *, 0xC);
}
