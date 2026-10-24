#include <m2c.h>

s32 func_020100a8(M2C_UNK);
void *func_ov017_021b8470(s32);
void *func_ov017_021b8478(s32);

void func_ov017_021c840c(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3) {
    s32 temp_r6;
    void *temp_r0;
    void *temp_r0_2;

    temp_r6 = M2C_FIELD(arg3, s32 *, 0x3718);
    temp_r0 = func_ov017_021b8478(temp_r6);
    if (temp_r0 == NULL) {
        return;
    }
    temp_r0_2 = func_ov017_021b8470(temp_r6);
    if (temp_r0_2 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r0, s8 *, 0x2A) == func_020100a8(arg2)) {
        return;
    }
    if (M2C_FIELD(temp_r0, u16 *, 8) == M2C_FIELD(arg1, u16 *, 4)) {
        M2C_FIELD(temp_r0_2, s32 *, 0x8E20) = (s32) M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_r0, u8 *, 5) = (u8) M2C_FIELD(arg1, u8 *, 6);
    }
}
