#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
s32 func_020100f8();
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020979f4();
M2C_UNK func_020a1e54(M2C_UNK);
M2C_UNK func_020a1f4c(M2C_UNK);
M2C_UNK func_020a27ac();
extern M2C_UNK data_02114e20;
extern s32 data_ov017_021d83ec;

void func_ov017_021b14ec(void *arg0) {
    s32 temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x1C) != 0) {
        func_020979f4();
    }
    data_ov017_021d83ec = 0;
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 8);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 8);
        func_02012da4(&data_02114e20, temp_r0);
    }
    func_020a1e54(1);
    func_020a1f4c(1);
    _ZN9GameState11GetInstanceEv();
    if (func_020100f8() == 0) {
        return;
    }
    func_020a27ac();
}
