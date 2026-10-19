#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_02012da4(M2C_UNK *, s32);
s32 func_02057924();
M2C_UNK func_02057f00(s32, M2C_UNK);
M2C_UNK func_0205ebec(M2C_UNK *);
extern M2C_UNK data_02108760;
extern M2C_UNK data_02114e20;

void func_ov017_021c310c(void *arg0) {
    s32 temp_r0;
    s32 temp_r4;

    if (M2C_FIELD(arg0, s32 *, 0x90) != 0) {
        temp_r4 = func_02057924();
        func_0205ebec(&data_02108760);
        func_02057f00(temp_r4, 0x11);
    }
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 8);
    if (temp_r0 == 0) {
        return;
    }
    _ZN13SafeAllocator7DestroyEv(arg0 + 8);
    func_02012da4(&data_02114e20, temp_r0);
}
