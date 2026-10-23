#include <m2c.h>

void _ZN16BackgroundLoader10RemoveTaskEi(void *, s32);
void * _ZN16BackgroundLoader11GetInstanceEv(void *);

void func_ov003_02153874(void *arg0) {
    s32 temp_r1;
    s32 temp_r1_2;
    void *temp_r0;

    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv(arg0);
    temp_r1 = M2C_FIELD(arg0, s32 *, 0x50);
    if (temp_r1 >= 0) {
        _ZN16BackgroundLoader10RemoveTaskEi(temp_r0, temp_r1);
    }
    temp_r1_2 = M2C_FIELD(arg0, s32 *, 0x54);
    if (temp_r1_2 >= 0) {
        _ZN16BackgroundLoader10RemoveTaskEi(temp_r0, temp_r1_2);
    }
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x50) = -1;
    M2C_FIELD(arg0, s32 *, 0x54) = -1;
    M2C_FIELD(arg0, s8 *, 0x5A) = 2;
    M2C_FIELD(arg0, s8 *, 0x5B) = 0;
    M2C_FIELD(arg0, s8 *, 0x5C) = 0;
    M2C_FIELD(arg0, u8 *, 0x5D) = (u8) (M2C_FIELD(arg0, u8 *, 0x5D) & ~2);
}
