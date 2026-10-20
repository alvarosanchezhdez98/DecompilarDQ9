#include <m2c.h>

u16 *func_02012fe4();

void func_0208b494(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xB0) != 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0xB0) = 1;
    M2C_FIELD(arg0, s32 *, 0xAC) = (s32) *func_02012fe4();
}
