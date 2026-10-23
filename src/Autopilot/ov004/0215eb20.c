#include <m2c.h>


u16 func_ov004_0215eb20(void *arg0, s32 arg1) {
    return (u16) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x150), u16 *, 0x954) & (1 << arg1));
}
