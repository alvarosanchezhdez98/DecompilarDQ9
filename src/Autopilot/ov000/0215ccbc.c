#include <m2c.h>


void func_ov000_0215ccbc(s32 arg0, void *arg1, void *arg2, s16 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7, u8 arg8) {
    if (arg1 == NULL) {
        return;
    }
    M2C_FIELD(arg1, s16 *, 0xC) = arg3;
    M2C_FIELD(arg1, s16 *, 0xE) = arg4;
    M2C_FIELD(arg1, s16 *, 0x10) = arg5;
    M2C_FIELD(arg1, u16 *, 0x12) = (u16) M2C_FIELD(M2C_FIELD(arg2, void **, 0x138), u16 *, 4);
    M2C_FIELD(arg1, u16 *, 0x14) = (u16) M2C_FIELD(M2C_FIELD(arg2, void **, 0x138), u16 *, 6);
    M2C_FIELD(arg1, s32 *, 0x18) = (s32) M2C_FIELD(M2C_FIELD(arg2, void **, 0x138), s32 *, 0x14);
    M2C_FIELD(arg1, s8 *, 0x1D) = (s8) ((u32) (M2C_FIELD(M2C_FIELD(arg2, void **, 0x138), u16 *, 0x22) << 0x1A) >> 0x1C);
    M2C_FIELD(arg1, s8 *, 0x1E) = (s8) ((u32) (M2C_FIELD(M2C_FIELD(arg2, void **, 0x138), u16 *, 0x22) << 0x1E) >> 0x1E);
    M2C_FIELD(arg1, s32 *, 0) = arg6;
    M2C_FIELD(arg1, s32 *, 4) = arg7;
    M2C_FIELD(arg1, u8 *, 0x1C) = arg8;
}
