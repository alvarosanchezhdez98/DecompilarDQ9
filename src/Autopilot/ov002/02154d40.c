#include <m2c.h>

M2C_UNK func_020e1368(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_020e1374(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_020e2490(void *, M2C_UNK, M2C_UNK, void *, void *, s32, s32);
void _ZN13SafeAllocator11CreateTypeAEPvj(void *, void *, u32);
void * _ZN13SafeAllocator8AllocateEj(void *, u32);

void func_ov002_02154d40(void *arg0, void *arg1) {
    s32 temp_r4;

    if (arg1 != NULL) {
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x810, _ZN13SafeAllocator8AllocateEj(arg1, 0x3C00U), 0x3C00U);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x83C, _ZN13SafeAllocator8AllocateEj(arg1, 0x5400U), 0x5400U);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x828, _ZN13SafeAllocator8AllocateEj(arg1, 0xD400U), 0xD400U);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x850, _ZN13SafeAllocator8AllocateEj(arg1, 0x4C00U), 0x4C00U);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x864, _ZN13SafeAllocator8AllocateEj(arg1, 0x9400U), 0x9400U);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x878, _ZN13SafeAllocator8AllocateEj(arg1, 0x800U), 0x800U);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x88C, _ZN13SafeAllocator8AllocateEj(arg1, 0x580U), 0x580U);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x8A0, _ZN13SafeAllocator8AllocateEj(arg1, 0x533U), 0x533U);
        M2C_FIELD(arg0, void **, 0x1A64) = _ZN13SafeAllocator8AllocateEj(arg1, 0x6B8U);
        M2C_FIELD(arg0, void **, 0x1A68) = _ZN13SafeAllocator8AllocateEj(arg1, 0x54U);
        M2C_FIELD(arg0, void **, 0x1A6C) = _ZN13SafeAllocator8AllocateEj(arg1, 8U);
        M2C_FIELD(arg0, void **, 0x1BD4) = _ZN13SafeAllocator8AllocateEj(arg1, 0x960U);
        M2C_FIELD(arg0, void **, 0) = _ZN13SafeAllocator8AllocateEj(arg1, 0x24U);
        M2C_FIELD(arg0, void **, 4) = _ZN13SafeAllocator8AllocateEj(arg1, 0x24U);
        func_020e2490(M2C_FIELD(arg0, void **, 0), 0, 0, NULL, arg1, 0xC, 0x40);
        func_020e2490(M2C_FIELD(arg0, void **, 4), 0, 1, M2C_FIELD(arg0, void **, 0x1A6C), arg1, 4, 0x60);
        temp_r4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0xC);
        func_020e1368(temp_r4 + 0xC, 0, 0x3000, 5);
        func_020e1374(temp_r4 + 0xC, 0x3800, 0x3000, 4);
    }
}
