#include <m2c.h>

void *func_ov004_02156ed0(M2C_UNK, M2C_UNK);
void * _ZN9GameState11GetInstanceEv(void);

s32 func_ov004_021570a4(M2C_UNK arg0, u32 arg1) {
    s32 temp_r4;

    if (arg1 >= 6U) {
        return 0;
    }
    temp_r4 = _ZN9GameState11GetInstanceEv() + 0x5E6C;
    return ((arg1 + (M2C_FIELD(func_ov004_02156ed0(arg0, 0x5B), s16 *, 0x5C) * 6)) * 0x28) + (temp_r4 + 4);
}
