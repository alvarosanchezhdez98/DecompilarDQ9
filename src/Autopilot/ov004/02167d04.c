#include <m2c.h>

M2C_UNK func_ov004_02167b78(void *, M2C_UNK);
extern M2C_UNK data_ov004_02171024;
void * _ZN10MenuScript8FindHeapEi(void *, s32);
void * _ZN13SafeAllocator8AllocateEj(void *, u32);

s32 func_ov004_02167d04(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN10MenuScript8FindHeapEi(arg0, 0);
    if (temp_r0 != NULL) {
        M2C_FIELD(&data_ov004_02171024, void **, 4) = _ZN13SafeAllocator8AllocateEj(temp_r0 + 4, 0xCU);
        M2C_FIELD(&data_ov004_02171024, void **, 0) = _ZN13SafeAllocator8AllocateEj(temp_r0 + 4, 0x80U);
        M2C_FIELD(&data_ov004_02171024, void **, 8) = _ZN13SafeAllocator8AllocateEj(temp_r0 + 4, 0x80U);
        func_ov004_02167b78(arg0, 0);
    }
    return 0;
}
