#include <m2c.h>

void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);
void func_0200fb94(void *arg0, s8 arg1);
void func_02012010(void *arg0, s32 arg1);

s32 func_ov004_0216dc24(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    func_0200fb94(temp_r0, 6);
    func_02012010(temp_r0, 2);
    _ZN10MenuScript10StartEntryEi(arg0, 0x3E7);
    return 0;
}
