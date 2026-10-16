#include <m2c.h>

s32 _Z16GetRandomStateHiP6Random(s32);
s32 _Z16GetRandomStateLoP6Random(s32);

void func_ov000_021605d0(void *arg0, void *arg1) {
    s32 temp_r4;

    M2C_FIELD(arg0, s32 *, 0x29C) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x2A0) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 8);
    temp_r4 = M2C_FIELD(arg0, s32 *, 0x29C);
    if (temp_r4 == 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x6E3C) = _Z16GetRandomStateHiP6Random(temp_r4);
    M2C_FIELD(arg0, s32 *, 0x6E40) = _Z16GetRandomStateLoP6Random(temp_r4);
}
