#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_02010828();
M2C_UNK func_02086778(s32, s8 *, M2C_UNK, M2C_UNK);
s32 func_ov017_021b6d60(M2C_UNK, s8 *);

s32 func_ov017_021b6c2c(M2C_UNK arg0, M2C_UNK arg1) {
    s8 sp0[572];

    if (func_ov017_021b6d60(arg0, sp0) == 0) {
        return -1;
    }
    _ZN9GameState11GetInstanceEv();
    func_02086778(func_02010828(), sp0, 0, arg1);
    return (s32) (sp0[0] << 0x1A) >> 0x1A;
}
