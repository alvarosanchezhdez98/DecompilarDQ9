#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
M2C_UNK _ZN20AtmosphericEffectSet5ResetEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_0201e248(void *);
M2C_UNK func_020de848(void *);
M2C_UNK func_02012fa4(void *);

void func_02013750(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x838) = 0;
    M2C_FIELD(arg0, s32 *, 0x83C) = 0;
    M2C_FIELD(arg0, s32 *, 0x424) = 0;
    M2C_FIELD(arg0, s32 *, 0x41C) = 0;
    M2C_FIELD(arg0, s32 *, 0x418) = 0;
    M2C_FIELD(arg0, s8 *, 0x476) = 0;
    M2C_FIELD(arg0, s8 *, 0x477) = 0;
    M2C_FIELD(arg0, s32 *, 0x82C) = 0;
    M2C_FIELD(arg0, s16 *, 0x474) = 0;
    M2C_FIELD(arg0, s32 *, 0x82C) = 0;
    M2C_FIELD(arg0, s8 *, 0x42C) = 0;
    M2C_FIELD(arg0, s32 *, 0x430) = -1;
    M2C_FIELD(arg0, s32 *, 0x434) = -1;
    M2C_FIELD(arg0, s32 *, 0x438) = -1;
    M2C_FIELD(arg0, s32 *, 0x43C) = -1;
    M2C_FIELD(arg0, s32 *, 0x440) = -1;
    M2C_FIELD(arg0, s32 *, 0x478) = 0;
    M2C_FIELD(arg0, s32 *, 0x47C) = 0;
    M2C_FIELD(arg0, s8 *, 0x23BC) = 0;
    M2C_FIELD(arg0, s8 *, 0x23BD) = 0;
    M2C_FIELD(arg0, s8 *, 0x834) = 0;
    func_0201e248(arg0 + 0x6C);
    func_020de848(arg0 + 0x2754);
    _ZN20AtmosphericEffectSet5ResetEv(arg0 + 0xF4);
    func_02012fa4(arg0 + 0x600);
    if (arg1 == 0) {
        return;
    }
    if (_ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x2730) != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x2730);
        _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x2730);
    }
    if (_ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x54) == 0) {
        return;
    }
    _ZN13SafeAllocator7DestroyEv(arg0 + 0x54);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x54);
}
