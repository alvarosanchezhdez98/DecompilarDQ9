#include <m2c.h>

M2C_UNK func_020134e0();

void func_02013718(void *arg0, s32 arg1, s32 arg2) {
    func_020134e0();
    M2C_FIELD(arg0, s32 *, 0x4C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x50) = arg2;
    M2C_FIELD(arg0, s32 *, 0x838) = 0;
    M2C_FIELD(arg0, s32 *, 0x83C) = 0;
    M2C_FIELD(arg0, s16 *, 0x474) = 0;
    M2C_FIELD(arg0, s32 *, 0x82C) = 0;
}
