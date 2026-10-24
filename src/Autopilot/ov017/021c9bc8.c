#include <m2c.h>

s32 func_0202c508(s32);
s32 func_0207d78c();
M2C_UNK func_0207da94(s32, u8);
M2C_UNK func_0207db58(s32, u16, s32);
M2C_UNK func_ov000_0216377c(s32, u16);
s32 func_ov017_021b8468(s32);
void *func_ov017_021b8478(s32);

void func_ov017_021c9bc8(s32 arg0, void *arg1, s32 arg2, void *arg3, s32 arg4) {
    s32 temp_r0;
    s32 temp_r4;
    u32 temp_r7;
    s32 temp_r5;
    u16 temp_r6;
    void *temp_r4_2;

    temp_r4 = func_0207d78c();
    temp_r5 = M2C_FIELD(arg1, u16 *, 4);
    temp_r6 = M2C_FIELD(arg1, u16 *, 6);
    if (func_0202c508(arg4) != 0) {
        func_0207da94(temp_r4, (u8) temp_r6);
        func_0207db58(temp_r4, temp_r5, arg0);
        return;
    }
    if (arg0 != 0) {
        return;
    }
    temp_r7 = M2C_FIELD(arg3, s32 *, 0x3718);
    temp_r4_2 = func_ov017_021b8478(temp_r7);
    temp_r0 = func_ov017_021b8468(temp_r7);
    if ((temp_r4_2 != NULL) && (temp_r0 != 0)) {
        if (M2C_FIELD(temp_r4_2, u16 *, 8) != temp_r5) {
            return;
        }
        func_ov000_0216377c(temp_r0, temp_r6);
    }
}
