#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_02010828();

s32 func_ov003_02160bd0(s32 arg0, s32 arg1) {
    if (arg1 < 0) {
        return 0;
    }
    _ZN9GameState11GetInstanceEv();
    return (arg1 * 0x23C) + (func_02010828() + 0xF80);
}
