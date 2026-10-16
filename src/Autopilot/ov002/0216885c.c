#include <m2c.h>

s32 func_02012444(M2C_UNK *, s32);
s32 func_02012aac(M2C_UNK *);
void *func_020421a0();
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;

void func_ov002_0216885c(void *arg0) {
    void *temp_r0;

    temp_r0 = func_020421a0();
    if (M2C_FIELD(temp_r0, s32 *, 0x998) != 0) {
        if ((u32) M2C_FIELD(arg0, u8 *, 0x2454) >= (u32) M2C_FIELD(arg0, u8 *, 0x2455)) {
            M2C_FIELD(arg0, s32 *, 0x1BC0) = (s32) (M2C_FIELD(arg0, s32 *, 0x1BC0) + 1);
        }
        if (M2C_FIELD(temp_r0, s32 *, 0x9A0) != 3) {
            return;
        }
        if ((func_02012444(&data_02114e30, 0x603) == 0) && (func_02012aac(&data_02114e54) == 0)) {
            return;
        }
        M2C_FIELD(arg0, s32 *, 0x1BC0) = (s32) (M2C_FIELD(arg0, s32 *, 0x1BC0) - 1);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x1BC0) = (s32) (M2C_FIELD(arg0, s32 *, 0x1BC0) + 1);
}
