#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_02010828();
M2C_UNK func_ov003_02160c58(M2C_UNK, s16 *, M2C_UNK *);

s32 func_ov003_021614e8(M2C_UNK arg0) {
    s16 sp2;
    s16 sp0;
    s32 temp_r4;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_02010828();
    temp_r4 = ((s16) (M2C_FIELD(temp_r0, u8 *, 0xF7C) + M2C_FIELD(temp_r0, u8 *, 0x2C8C)) - 1) << 0x10;
    func_ov003_02160c58(arg0, &sp2, &sp0);
    if ((s32) sp2 <= (s32) (temp_r4 >> 0x10)) {
        return 1;
    }
    return 0;
}
