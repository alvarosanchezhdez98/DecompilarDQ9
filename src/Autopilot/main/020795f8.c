#include <m2c.h>


void func_020795e8(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s8 *, 0x138) = (s8) ((u32) (M2C_FIELD(arg1, s32 *, 4) << 0x1D) >> 0x1D);
    M2C_FIELD(arg0, s8 *, 0x139) = (s8) ((u32) (M2C_FIELD(arg1, s32 *, 4) << 0x1A) >> 0x1D);
    M2C_FIELD(arg0, s8 *, 0x13A) = (s8) ((u32) (M2C_FIELD(arg1, s32 *, 4) << 0x17) >> 0x1D);
    M2C_FIELD(arg0, s8 *, 0x13B) = (s8) ((u32) (M2C_FIELD(arg1, s32 *, 4) << 0x14) >> 0x1D);
    M2C_FIELD(arg0, s8 *, 0x13C) = (s8) ((u32) (M2C_FIELD(arg1, s32 *, 4) << 0x11) >> 0x1D);
    M2C_FIELD(arg0, s32 *, 0x140) = (s32) M2C_FIELD(arg1, u8 *, 2);
    M2C_FIELD(arg0, s32 *, 0x144) = (s32) M2C_FIELD(arg1, s8 *, 3);
}
