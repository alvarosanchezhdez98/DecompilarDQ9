#include <m2c.h>

M2C_UNK _Z19ZeroInitializeMutexP5Mutex(M2C_UNK *);
extern s32 data_ov031_02290f88;
extern M2C_UNK data_ov031_02290f8c;

s32 ov38_0222175C(void) {
    _Z19ZeroInitializeMutexP5Mutex(&data_ov031_02290f8c);
    data_ov031_02290f88 = 0;
    return 1;
}
