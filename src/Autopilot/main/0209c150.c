#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_02010828();
s32 func_02086b98();

s32 func_0209c140(void) {
    if ((_ZN9GameState11GetInstanceEv() != 0) && (func_02010828() != 0) && (func_02086b98() != 0)) {
        return 1;
    }
    return 0;
}
