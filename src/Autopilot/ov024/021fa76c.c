#include <m2c.h>

s32 func_02010088();
s32 func_020882f8(s32);
s32 func_ov024_021da9b0(void *);
s32 func_ov024_021da9c8(void *);
s32 func_ov024_021de25c(void *);
s32 func_ov024_021e6798(void *);

s32 func_ov024_021fa76c(void *arg0) {
    if (func_02010088() != 0) {
        return 0;
    }
    if (func_ov024_021e6798(arg0) != 0) {
        return 0;
    }
    if (func_ov024_021da9b0(arg0) != 0) {
        return 0;
    }
    if (func_020882f8(M2C_FIELD(arg0, s32 *, 0x138)) != 0) {
        return 0;
    }
    if (func_ov024_021da9c8(arg0) != 0) {
        return 0;
    }
    if (func_ov024_021de25c(arg0) == 0) {
        return 1;
    }
    return 0;
}
