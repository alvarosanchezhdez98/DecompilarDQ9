#include <m2c.h>

M2C_UNK func_0203ef7c();
s32 rand();

void func_0203c794(void *arg0) {
    func_0203ef7c();
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, s32 *, 0x68) = 0x324;
    M2C_FIELD(arg0, s32 *, 0x84) = (s32) (4096.0f * ((f32) (rand() % 200) / 100.0f));
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x88) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0x7A;
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, s8 *, 0x94) = 0xF;
    M2C_FIELD(arg0, s8 *, 0x95) = 0;
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
}
