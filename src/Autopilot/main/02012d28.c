#include <m2c.h>

s32 _ZN13HPXEAllocator16CreateAtLocationEPvjt(s32, u32, M2C_UNK);
M2C_UNK _ZN14AllocatorUnion15InitializeTypeBEP13HPXEAllocatori(M2C_UNK, s32, M2C_UNK);
s32 func_020c8520(M2C_UNK);
s32 func_020c8534(M2C_UNK);
s32 func_020c86fc(M2C_UNK, u32, M2C_UNK);
M2C_UNK func_020c9be0();

void func_02012d18(M2C_UNK arg0) {
    s32 temp_r4;
    u32 temp_r4_2;

    temp_r4 = func_020c8534(0);
    temp_r4_2 = (func_020c8520(0) & ~0xF) - ((temp_r4 + 0xF) & ~0xF);
    _ZN14AllocatorUnion15InitializeTypeBEP13HPXEAllocatori(arg0, _ZN13HPXEAllocator16CreateAtLocationEPvjt(func_020c86fc(0, temp_r4_2, 0x10), temp_r4_2, 0), 4);
    if (temp_r4_2 >= 0x12D0F4U) {
        return;
    }
    func_020c9be0();
}
