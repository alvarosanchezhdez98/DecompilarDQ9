#include <m2c.h>

M2C_UNK _ZN13SafeAllocator11CreateTypeAEPvj(void *, s32, M2C_UNK);
s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
void *func_020421a0();
M2C_UNK func_020c9be0();

void func_ov003_0215c568(void *arg0, s32 arg1) {
    s32 var_r4;
    s32 var_r5;
    void *var_r6;

    var_r5 = arg1;
    var_r6 = arg0;
    if (var_r5 == 0) {
        return;
    }
    var_r4 = _ZN13SafeAllocator8AllocateEj(var_r5, 0x2000);
    if (var_r4 == 0) {
        func_020c9be0();
    }
    _ZN13SafeAllocator11CreateTypeAEPvj(var_r6, var_r4, 0x2000);
    var_r4 = _ZN13SafeAllocator8AllocateEj(var_r5, 0x800);
    if (var_r4 == 0) {
        func_020c9be0();
    }
    _ZN13SafeAllocator11CreateTypeAEPvj(var_r6 + 0x14, var_r4, 0x800);
    var_r4 = _ZN13SafeAllocator8AllocateEj(var_r5, 0x4000);
    if (var_r4 == 0) {
        func_020c9be0();
    }
    _ZN13SafeAllocator11CreateTypeAEPvj(var_r6 + 0x28, var_r4, 0x4000);
    var_r4 = _ZN13SafeAllocator8AllocateEj(var_r5, 0x400);
    if (var_r4 == 0) {
        func_020c9be0();
    }
    _ZN13SafeAllocator11CreateTypeAEPvj(var_r6 + 0x3C, var_r4, 0x400);
    var_r4 = _ZN13SafeAllocator8AllocateEj(var_r5, 0x2000);
    if (var_r4 == 0) {
        func_020c9be0();
    }
    _ZN13SafeAllocator11CreateTypeAEPvj(var_r6 + 0x50, var_r4, 0x2000);
    M2C_FIELD(var_r6, s32 *, 0x7C) = (s32) M2C_FIELD(func_020421a0(), s32 *, 0x5C);
}
