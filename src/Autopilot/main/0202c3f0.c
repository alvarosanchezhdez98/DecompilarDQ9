#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_02010890(s32, M2C_UNK *, s32 *);

void func_0202c3e0(void *arg0) {
    M2C_UNK sp4[4];
    s32 sp0;

    func_02010890(_ZN9GameState11GetInstanceEv(), sp4, &sp0);
    M2C_FIELD(arg0, s8 *, 0x1027) = (s8) sp0;
}
