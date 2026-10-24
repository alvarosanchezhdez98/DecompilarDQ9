#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_0200fd48(s32, s32);

void func_02057db8(s32 arg0, s32 arg1) {
    if (arg1 < 0xD0) {
        return;
    }
    if (arg1 > 0xDF) {
        return;
    }
    func_0200fd48(_ZN9GameState11GetInstanceEv(), arg1);
}
