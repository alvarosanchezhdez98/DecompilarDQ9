#include <m2c.h>

M2C_UNK _ZN13SafeAllocator11CreateTypeAEPvj(s32, s32, M2C_UNK);
s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);

void func_ov003_0215f8cc(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        return;
    }
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x228, _ZN13SafeAllocator8AllocateEj(arg1, 0x1000), 0x1000);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x23C, _ZN13SafeAllocator8AllocateEj(arg1, 0x7000), 0x7000);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x264, _ZN13SafeAllocator8AllocateEj(arg1, 0x2000), 0x2000);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x278, _ZN13SafeAllocator8AllocateEj(arg1, 0x7400), 0x7400);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x28C, _ZN13SafeAllocator8AllocateEj(arg1, 0x4C00), 0x4C00);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x2A0, _ZN13SafeAllocator8AllocateEj(arg1, 0xC00), 0xC00);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x2B4, _ZN13SafeAllocator8AllocateEj(arg1, 0x3C00), 0x3C00);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x2C8, _ZN13SafeAllocator8AllocateEj(arg1, 0x200), 0x200);
}
