#include <m2c.h>


void func_ov017_021d6148(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0) == 3) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 4) = arg1;
    }
}
