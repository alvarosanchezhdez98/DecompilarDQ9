#include <m2c.h>

void *func_0207f6ac();

void func_0207f7ac(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_r0;

    temp_r0 = func_0207f6ac();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, u8 *, 0x2A) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x2A) | arg2);
    }
}
