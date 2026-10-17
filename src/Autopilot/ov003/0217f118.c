#include <m2c.h>

s32 GetMainBGAssignedVRAMSize();
M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_02074bd0(void *);
M2C_UNK func_020a0c0c();
M2C_UNK func_020a1e54(M2C_UNK);
M2C_UNK func_020ca458(M2C_UNK, M2C_UNK, s32);
M2C_UNK func_ov003_0216d77c();
extern M2C_UNK data_02114e20;

void func_ov003_0217f118(void *arg0) {
    s32 temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        func_ov003_0216d77c();
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
        func_020a1e54(1);
    }
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x14);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x14);
        func_02012da4(&data_02114e20, temp_r0);
    }
    func_02074bd0(arg0 + 0x2A);
    func_020ca458(0, 0x06000000, GetMainBGAssignedVRAMSize());
    func_020a0c0c();
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
