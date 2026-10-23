#include <m2c.h>

M2C_UNK func_0202e5d8(void *, s32, s32, s32);

void func_0202e6a8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x70) = arg1;
    func_0202e5d8(arg0, arg1, M2C_FIELD(arg0, s32 *, 0x74), M2C_FIELD(arg0, s32 *, 0x78));
}
