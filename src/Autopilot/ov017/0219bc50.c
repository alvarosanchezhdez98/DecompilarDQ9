#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN13SafeAllocator5ResetEv(void *);
M2C_UNK _ZN7Model3D5ClearEv(s32);
M2C_UNK _ZN8Object3D10InitializeEv(s32);
M2C_UNK func_0207df50(void *);

void func_ov017_0219bc50(void *arg0) {
    _ZN7Model3D5ClearEv(M2C_FIELD(arg0, s32 *, 0x36C8));
    _ZN8Object3D10InitializeEv(M2C_FIELD(arg0, s32 *, 0x36CC));
    _ZN13SafeAllocator5ResetEv(arg0 + 0xB0);
    func_0207df50(arg0 + 0x56C);
}
