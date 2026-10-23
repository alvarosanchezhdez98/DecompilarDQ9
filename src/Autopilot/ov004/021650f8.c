#include <m2c.h>

s32 func_02011930(void *, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_020119f8(void *, M2C_UNK);
M2C_UNK func_02011a40();
s32 func_0203b5f8(s32, M2C_UNK);
void *func_020421a0();
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0218d77c(s32, M2C_UNK);
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);

s32 func_ov004_021650f8(void *arg0) {
    s32 temp_r0;
    void *temp_r5;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r0 = func_ov017_0218b5b0();
    if ((func_0203b5f8(temp_r0, 0) == 0) || (func_0203b5f8(temp_r0, 1) == 0)) {
        return 0;
    }
    if (M2C_FIELD(func_020421a0(), s32 *, 0x998) != 0) {
        return 0;
    }
    if (func_02011930(temp_r5, 0, 0, 0) != 0) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x6B);
    } else if (func_020119f8(temp_r5, 0) != 0) {
        _ZN9GameState11GetInstanceEv();
        func_02011a40();
        func_ov017_0218d77c(func_ov017_0218b5b0(), 2);
        _ZN10MenuScript10StartEntryEi(arg0, 0x64);
    } else {
        _ZN10MenuScript10StartEntryEi(arg0, 0x64);
    }
    return 0;
}
