#include <m2c.h>

M2C_UNK _ZN8Object3D10EnableFlagEi(s32, s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState21GetPartyMemberByIndexEi(s32, s32);
M2C_UNK func_020466e4(s32, s32);
s32 func_020d6c00();

void func_020a8ac8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) | (1 << arg1));
    func_020466e4(func_020d6c00(), 0x402);
    _ZN8Object3D10EnableFlagEi(_ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), arg1), 0x08000100);
}
