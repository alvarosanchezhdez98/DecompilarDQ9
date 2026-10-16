#include <m2c.h>

M2C_UNK func_0207df90();
M2C_UNK func_0207dfac(s32);
M2C_UNK func_020553ec(void *, s32, s32, s32, s32);

void func_020555a0(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 4) != 0) && (M2C_FIELD(arg0, s32 *, 0xC) != 0) && (M2C_FIELD(arg0, s32 *, 0x10) != 0) && (M2C_FIELD(arg0, s32 *, 8) != 0)) {
        func_0207df90();
        func_020553ec(arg0, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x10));
        func_0207dfac(M2C_FIELD(arg0, s32 *, 8));
    }
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
}
