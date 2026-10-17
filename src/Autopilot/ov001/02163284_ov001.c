#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState12GetTickCountEv();
M2C_UNK func_ov017_021d6134(M2C_UNK, s32);

s32 func_ov001_02163284(M2C_UNK arg0) {
    _ZN9GameState11GetInstanceEv();
    func_ov017_021d6134(arg0, _ZNK9GameState12GetTickCountEv());
    return 1;
}
