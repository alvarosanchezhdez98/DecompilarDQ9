#include <m2c.h>

M2C_UNK memcpy(void *, M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov004_02170444;
void _ZN10MenuScript12SetCallbacksEPPFiPS_Ej(void *, void *, u32);
void * _ZN13SafeAllocator8AllocateEj(void *, u32);

void func_ov004_021633ac(void *arg0, void *arg1) {
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(arg0, 0x60U);
    memcpy(temp_r0, &data_ov004_02170444, 0x60);
    _ZN10MenuScript12SetCallbacksEPPFiPS_Ej(arg1, temp_r0, 0x18U);
}
