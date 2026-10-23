#include <m2c.h>

M2C_UNK func_0208b8c4(void *, void *);
M2C_UNK func_0208b9a0(void *, M2C_UNK);
void * _ZN10MenuScript8FindHeapEi(void *, s32);
void _ZN13SafeAllocator11CreateTypeAEPvj(void *, void *, u32);
void _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
void * _ZN13SafeAllocator8AllocateEj(void *, u32);
void _ZN15MenuObjectClass10InitializeEv(void *);

s32 func_ov004_02167820(void *arg0, void *arg1, s16 arg2, u16 arg3) {
    void *temp_r0;

    _ZN15MenuObjectClass10InitializeEv(arg0);
    M2C_FIELD(arg0, s16 *, 4) = 0x15;
    M2C_FIELD(arg0, s16 *, 6) = arg2;
    M2C_FIELD(arg0, u16 *, 8) = arg3;
    M2C_FIELD(arg0, s32 *, 0x1C) = 2;
    temp_r0 = _ZN10MenuScript8FindHeapEi(arg1, (s32) M2C_FIELD(arg0, u16 *, 8));
    if (temp_r0 == NULL) {
        return 0;
    }
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x20);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x20, _ZN13SafeAllocator8AllocateEj(temp_r0 + 4, 0x2800U), 0x2800U);
    func_0208b9a0(arg0 + 0x34, 1);
    func_0208b8c4(arg0 + 0x34, arg0 + 0x20);
    M2C_FIELD(arg0, s16 *, 0x106) = 0x270F;
    return 1;
}
