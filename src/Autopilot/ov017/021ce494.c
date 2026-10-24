#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState21GetPartyMemberByIndexEi(s32, M2C_UNK);
M2C_UNK func_0202ae18();
s32 func_0202ae24();
s32 func_0202c508();
M2C_UNK func_0205e330(s32, s8 *, M2C_UNK);

void func_ov017_021ce494(void) {
    s8 sp0[20];
    s32 temp_r0;

    func_0202ae18();
    if ((func_0202c508() == 0) && (_ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), 0xCE) == 0)) {
        temp_r0 = func_0202ae24();
        sp0[0] = 0x28;
        func_0205e330(temp_r0, sp0, 0);
    }
}
