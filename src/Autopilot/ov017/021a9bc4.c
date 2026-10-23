#include <m2c.h>

void *_ZN9GameState11GetInstanceEv();
M2C_UNK func_0204693c();

void func_ov017_021a9bc4(void *arg0, s8 arg1) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x3B;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0x26C) = 0;
    M2C_FIELD(_ZN9GameState11GetInstanceEv(), s8 *, 0x64DE) = arg1;
}
