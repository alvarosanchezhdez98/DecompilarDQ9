#include <m2c.h>


void func_0203b520(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & ~arg1);
}
