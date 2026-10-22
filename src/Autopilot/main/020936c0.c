#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_0200fb40();
M2C_UNK func_020421a0();
M2C_UNK func_02043204();
M2C_UNK func_02094a00();
M2C_UNK func_02094ab0();

void func_020936b0(void *arg0) {
    func_02094a00();
    func_02094ab0();
    M2C_FIELD(arg0, u8 *, 0x37) = (u8) (M2C_FIELD(arg0, u8 *, 0x37) & ~4);
    func_020421a0();
    func_02043204();
    M2C_FIELD(arg0, s16 *, 0x30) = -1;
    M2C_FIELD(arg0, s8 *, 0x34) = 4;
    M2C_FIELD(arg0, s8 *, 0x35) = 0;
    _ZN9GameState11GetInstanceEv();
    func_0200fb40();
}
