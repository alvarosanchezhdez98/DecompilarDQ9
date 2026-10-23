#include <m2c.h>

s32 func_02011930(void *, M2C_UNK, M2C_UNK, M2C_UNK);
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);
u8 func_020119cc(void *arg0);

s32 func_ov004_021658b0(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (func_02011930(temp_r0, 0, 0, 0) != 0) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x64);
        M2C_FIELD(_ZN9GameState11GetInstanceEv(), s8 *, 0x646E) = 1;
        func_020119cc(temp_r0);
    } else {
        _ZN10MenuScript10StartEntryEi(arg0, 0x65);
    }
    return 0;
}
