#include <m2c.h>

M2C_UNK func_02082d38(s32, s32);

void func_02089494(void *arg0, s32 arg1, void *arg2) {
    s32 temp_r1;
    s32 temp_r1_2;

    M2C_FIELD(arg0, u16 *, 4) = (u16) M2C_FIELD(arg2, u16 *, 0x30);
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(arg2, u16 *, 0x32);
    func_02082d38(arg0 + 0x3E, arg1 + 9);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) M2C_FIELD(arg2, u16 *, 0x38);
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(arg2, u16 *, 0x34);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(arg2, u16 *, 0x36);
    temp_r1 = (M2C_FIELD(arg0, s32 *, 0x10) & ~0x3FF) | ((-0x400U >> 0x16) & (u16) ((u32) (M2C_FIELD(arg2, s32 *, 0x3C) << 0x16) >> 0x16));
    M2C_FIELD(arg0, s32 *, 0x10) = temp_r1;
    temp_r1_2 = (temp_r1 & 0xFFF003FF) | ((u32) ((u16) ((u32) (M2C_FIELD(arg2, s32 *, 0x3C) << 0xC) >> 0x16) << 0x16) >> 0xC);
    M2C_FIELD(arg0, s32 *, 0x10) = temp_r1_2;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) ((temp_r1_2 & 0xC00FFFFF) | ((u32) ((u16) ((u32) (M2C_FIELD(arg2, s32 *, 0x3C) * 4) >> 0x16) << 0x16) >> 2));
}
