#include <m2c.h>

M2C_UNK LoadToMainBG1CharacterData(s32, M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, M2C_UNK);
M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_0205a494(s32);
M2C_UNK func_0205d048(s32);
M2C_UNK func_0205d1e0(s32);
M2C_UNK func_0205d274(s32);
M2C_UNK func_0205d2bc(s32);
M2C_UNK func_0205d6a0(s32, M2C_UNK);
M2C_UNK func_02074bd0(s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov003_021700dc(void *arg0) {
    s32 temp_r0;

    func_0205a494(arg0 + 0x68);
    if (_ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0xBC) != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0xBC);
    }
    func_02074bd0(arg0 + 0x48);
    *(s32 *)0x04000000 = (*(s32 *)0x04000000 & ~0x1F00) | (M2C_FIELD(arg0, s32 *, 0x5C) << 8);
    temp_r0 = M2C_FIELD(arg0, s32 *, 0x3C);
    if (temp_r0 != 0) {
        func_0205d6a0(temp_r0, 1);
        func_0205d1e0(M2C_FIELD(arg0, s32 *, 0x3C));
        func_0205d274(M2C_FIELD(arg0, s32 *, 0x3C));
        func_0205d2bc(M2C_FIELD(arg0, s32 *, 0x3C));
        func_0205d048(M2C_FIELD(arg0, s32 *, 0x3C));
    }
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    memset(M2C_FIELD(arg0, s32 *, 0x14), 0, 0x20);
    _Z25CleanInvalidateCacheRangePKvj(M2C_FIELD(arg0, s32 *, 0x14), 0x20);
    LoadToMainBG1CharacterData(M2C_FIELD(arg0, s32 *, 0x14), 0, 0x20);
    *(s16 *)0x04000050 = 0;
}
