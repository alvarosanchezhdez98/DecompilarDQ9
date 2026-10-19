#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState20GetUnknownGameObjectEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020397c0();
s32 func_02057924();
M2C_UNK func_02057f00(s32, M2C_UNK);
M2C_UNK func_0205ebec(M2C_UNK *);
M2C_UNK func_020a0c0c();
extern M2C_UNK data_02108760;
extern M2C_UNK data_02114e20;

void func_ov017_021a7280(s32 arg0) {
    s32 temp_r0;

    func_02057f00(func_02057924(), 0xD);
    _ZN9GameState11GetInstanceEv();
    _ZN9GameState20GetUnknownGameObjectEv();
    func_020397c0();
    func_0205ebec(&data_02108760);
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x30);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x30);
        func_02012da4(&data_02114e20, temp_r0);
    }
    func_020a0c0c();
}
