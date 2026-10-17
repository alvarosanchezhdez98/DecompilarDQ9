#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv();
M2C_UNK func_020397cc(s32, M2C_UNK);
M2C_UNK func_02046a3c(s32, s32);
M2C_UNK func_ov017_021a5568(s32);

void func_ov017_021a5530(void *arg0) {
    _ZN9GameState11GetInstanceEv();
    func_020397cc(_ZN9GameState20GetUnknownGameObjectEv(), 1);
    func_ov017_021a5568(M2C_FIELD(arg0, s32 *, 0x371C));
    func_02046a3c(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, s32 *, 0x371C));
}
