#include <m2c.h>

M2C_UNK _ZN13SafeAllocator5ResetEv(void *);
M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_0200fb8c();
s32 func_020100bc(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_0202e874(s32, M2C_UNK);
M2C_UNK func_0202e9a4(s32, M2C_UNK);
M2C_UNK func_0202eab8(s32);
extern M2C_UNK data_02114e20;

void func_02046f84(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    func_0200fb8c();
    temp_r0 = func_020100bc(temp_r4);
    func_0202e874(temp_r0, 0);
    func_0202e9a4(temp_r0, 0xF000);
    func_0202eab8(temp_r0);
    if (M2C_FIELD(arg0, s32 *, 0x38) == 0) {
        temp_r0_2 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x24);
        if (temp_r0_2 != 0) {
            _ZN13SafeAllocator5ResetEv(arg0 + 0x24);
            _ZN13SafeAllocator7DestroyEv(arg0 + 0x24);
            func_02012da4(&data_02114e20, temp_r0_2);
        }
    }
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}
