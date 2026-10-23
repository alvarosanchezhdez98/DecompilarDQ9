#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState20GetUnknownGameObjectEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020397c0();
M2C_UNK func_0203b4b0(s32, M2C_UNK);
M2C_UNK func_020466f4(s32, M2C_UNK);
s32 func_020d6c00();
s32 func_ov017_0218b5b0();
extern M2C_UNK data_02114e20;

void func_020d9d60(s32 arg0) {
    s32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    _ZN9GameState20GetUnknownGameObjectEv();
    func_020397c0();
    func_0203b4b0(func_ov017_0218b5b0(), 0x10);
    func_020466f4(func_020d6c00(), 0xE);
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x58);
    if (temp_r0 == 0) {
        return;
    }
    _ZN13SafeAllocator7DestroyEv(arg0 + 0x58);
    func_02012da4(&data_02114e20, temp_r0);
}
