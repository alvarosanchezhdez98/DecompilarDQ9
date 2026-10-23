#include <m2c.h>

s32 func_02086aec(s32, s32);
void _ZN10MenuScript10StartEntryEi(void *, s32);
void * _ZN9GameState11GetInstanceEv(void);
s32 func_02010828(s32 arg0);

s32 func_ov004_02167e6c(void *arg0) {
    if (func_02086aec(func_02010828((s32) _ZN9GameState11GetInstanceEv()), 0x5617) > 0) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x1F);
    } else {
        _ZN10MenuScript10StartEntryEi(arg0, 0x32);
    }
    return 0;
}
