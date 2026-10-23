#include <m2c.h>

s32 ExtractFileFromGP2(M2C_UNK *, M2C_UNK *, s32 *);
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_020d3c84(void *, s32, s32);
extern M2C_UNK data_020f22e0;
extern M2C_UNK data_020f22f4;

void func_020d3c28(void *arg0) {
    s32 sp0;
    s32 temp_r0;

    memset(arg0, 0, 0xB4);
    M2C_FIELD(arg0, s32 *, 0xB4) = 0;
    _ZN16BackgroundLoader13AddLockGlobalEv();
    temp_r0 = ExtractFileFromGP2(&data_020f22e0, &data_020f22f4, &sp0);
    if (temp_r0 != 0) {
        func_020d3c84(arg0, temp_r0, sp0);
    }
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
}
