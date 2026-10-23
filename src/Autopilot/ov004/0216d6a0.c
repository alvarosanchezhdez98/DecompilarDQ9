#include <m2c.h>

void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);
void func_0200fb94(void *arg0, s8 arg1);
void func_02012028(void *arg0, s8 arg1);

s32 func_ov004_0216d6a0(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    func_0200fb94(temp_r0, 8);
    func_02012028(temp_r0, 0);
    _ZN10MenuScript10StartEntryEi(arg0, 0x3E7);
    return 0;
}
