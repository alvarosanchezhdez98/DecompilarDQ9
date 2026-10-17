#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
M2C_UNK _ZN16BackgroundLoader10RemoveTaskEi(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
void *func_020421a0();
s32 func_0205ec34();
void *func_02094d6c();
M2C_UNK memcpy(s32, void *, M2C_UNK);
extern void *data_ov004_0217101c;

s32 func_ov004_02166ac4(void) {
    void *temp_r4;

    temp_r4 = data_ov004_0217101c;
    _ZN16BackgroundLoader10RemoveTaskEi(_ZN16BackgroundLoader11GetInstanceEv(), M2C_FIELD(temp_r4, s32 *, 0x44));
    M2C_FIELD(temp_r4, s32 *, 0x44) = -1;
    _ZN13SafeAllocator7DestroyEv(temp_r4 + 0x30);
    _ZN13SafeAllocator7DestroyEv(temp_r4 + 0x1C);
    memcpy(func_0205ec34() + 0x2CC, data_ov004_0217101c + 0x51, 0x66);
    M2C_FIELD(func_02094d6c(), s32 *, 0xA0) = (s32) M2C_FIELD(data_ov004_0217101c, s32 *, 0xB8);
    M2C_FIELD(func_020421a0(), s8 *, 0x1962) = 0;
    return 0;
}
