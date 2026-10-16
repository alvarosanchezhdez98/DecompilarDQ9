#include <m2c.h>

M2C_UNK _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader8GetFlag0Ev();
s32 func_ov025_021eb0f4(s32);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e413c(void) {
    _ZN16BackgroundLoader11GetInstanceEv();
    if (_ZN16BackgroundLoader8GetFlag0Ev() == 0) {
        return 0;
    }
    return func_ov025_021eb0f4(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC));
}
