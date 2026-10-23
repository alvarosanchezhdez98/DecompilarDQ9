#include <m2c.h>

extern M2C_UNK data_ov004_02171034;
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);
void func_02012028(void *arg0, s8 arg1);

s32 func_ov004_0216e8b4(void *arg0) {
    M2C_FIELD(&data_ov004_02171034, s8 *, 2) = 1;
    func_02012028(_ZN9GameState11GetInstanceEv(), 0);
    _ZN10MenuScript10StartEntryEi(arg0, 0x3E7);
    return 0;
}
