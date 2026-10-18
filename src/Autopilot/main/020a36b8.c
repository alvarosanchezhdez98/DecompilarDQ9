#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_020100a8();

s32 func_020a36a8(void *arg0) {
    _ZN9GameState11GetInstanceEv();
    if (M2C_FIELD(arg0, s8 *, 0x2A) == func_020100a8()) {
        return 1;
    }
    return 0;
}
