#include <m2c.h>

M2C_UNK _ZN12MemberScreen6Draw3DEv();

void func_ov017_021a185c(void *arg0) {
    if ((u32) M2C_FIELD(arg0, u8 *, 0x22) <= 1U) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C) == 0) {
        return;
    }
    _ZN12MemberScreen6Draw3DEv();
}
