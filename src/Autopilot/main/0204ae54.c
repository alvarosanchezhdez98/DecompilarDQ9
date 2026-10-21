#include <m2c.h>

M2C_UNK func_0204ae7c(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);

void func_0204ae44(void *arg0, M2C_UNK arg1) {
    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        func_0204ae7c(arg0, arg1, 0, 0, (s32) M2C_FIELD(arg0, s16 *, 0), (s32) M2C_FIELD(arg0, s16 *, 2));
    }
}
