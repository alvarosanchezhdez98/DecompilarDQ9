#include <m2c.h>

void *func_0207f6ac(s32);

void func_0208103c(s32 arg0, s32 arg1, s16 arg2) {
    void *temp_r0;

    temp_r0 = func_0207f6ac(arg0 + 4);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s16 *, 0xE) = arg2;
    }
}
