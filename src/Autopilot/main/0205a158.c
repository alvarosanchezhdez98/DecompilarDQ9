#include <m2c.h>

M2C_UNK _ZN8Object3D4DrawEb(void *, u32);
M2C_UNK func_0205578c();

void func_0205a148(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s16 *, 0xB0) > 0) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0xAC) == 0) {
        _ZN8Object3D4DrawEb(arg0, (u32) (M2C_FIELD(arg0, u8 *, 0xCC) << 0x1D) >> 0x1F);
        return;
    }
    func_0205578c();
}
