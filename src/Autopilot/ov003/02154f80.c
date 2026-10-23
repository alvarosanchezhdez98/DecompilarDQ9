#include <m2c.h>

M2C_UNK func_02059f38(void *, void *);
void _ZN8Object3D14AdvanceEffectsEv(void *);
u8 _ZN8Object3D4DrawEb(void *, u8);
void * _ZN9GameState11GetInstanceEv(void);
void * _ZN9GameState21GetPartyMemberByIndexEi(void *, s32);

void func_ov003_02154f80(void *arg0) {
    void *temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x32C) == 0) {
        return;
    }
    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), (s32) M2C_FIELD(arg0, s8 *, 0x1F7));
    if (temp_r0 != NULL) {
        func_02059f38(arg0 + 0x280, temp_r0 + 0x44);
    }
    _ZN8Object3D14AdvanceEffectsEv(arg0 + 0x280);
    _ZN8Object3D4DrawEb(arg0 + 0x280, 1U);
}
