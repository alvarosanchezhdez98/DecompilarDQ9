#include <m2c.h>

M2C_UNK _ZN13SafeAllocator4FreeEPv();
M2C_UNK _ZN13SafeAllocator7DestroyEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv();
M2C_UNK func_02012da4();
M2C_UNK func_ov001_0215aa5c();
extern M2C_UNK data_02114e20;

void func_ov017_021bb108(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;

    if (_ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x7C) != 0) {
        func_ov001_0215aa5c();
        temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x124);
        if (temp_r0 != 0) {
            _ZN13SafeAllocator7DestroyEv(arg0 + 0x124);
            _ZN13SafeAllocator4FreeEPv(arg0 + 0x7C, temp_r0);
        }
        temp_r4 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x7C);
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x7C);
        func_02012da4(&data_02114e20, temp_r4);
    }
    if (M2C_FIELD(arg0, s32 *, 0x138) == 0) {
        return;
    }
    temp_r0_2 = _ZNK13SafeAllocator18GetSignedAllocatorEv();
    if (temp_r0_2 == 0) {
        return;
    }
    _ZN13SafeAllocator7DestroyEv(M2C_FIELD(arg0, s32 *, 0x138));
    func_02012da4(&data_02114e20, temp_r0_2);
    M2C_FIELD(arg0, s32 *, 0x138) = 0;
}
