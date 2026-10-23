#include <m2c.h>

s32 func_0204c7cc();
s32 func_0205bd20(s32);
void *func_0205d81c(void *, u8);

s32 func_0205da38(void *arg0) {
    void *temp_r0;

    if (func_0205bd20(arg0 + 4) != 0) {
        temp_r0 = func_0205d81c(arg0, M2C_FIELD(arg0, u8 *, 0xB0));
        if ((temp_r0 != NULL) && (func_0204c7cc() != 0) && (M2C_FIELD(temp_r0, u8 *, 0xC5) & 2)) {
            return 1;
        }
    }
    return 0;
}
