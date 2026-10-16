#include <m2c.h>


s32 SOCLi_RoundUp4(s32 arg0) {
    return (arg0 + 3) & ~3;
}
