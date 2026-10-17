#include <m2c.h>

M2C_UNK _ZN14ItemInfoWindow5CloseEv(s32);
M2C_UNK func_020466f4(s32, M2C_UNK);
s32 func_020d6c00();

void func_ov003_021749c0(void *arg0) {
    _ZN14ItemInfoWindow5CloseEv(arg0 + 0x3C);
    M2C_FIELD(arg0, u16 *, 0x1046) = (u16) (M2C_FIELD(arg0, u16 *, 0x1046) & ~0x800);
    func_020466f4(func_020d6c00(), 1);
}
