#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_02012da4(M2C_UNK *, s32);
void *func_0202ae18();
s32 func_02046b60(s32, M2C_UNK);
M2C_UNK func_020a0c0c();
M2C_UNK func_020a1e54(M2C_UNK);
void *func_ov017_0218b5b0();
extern M2C_UNK data_02114e20;

void func_ov017_021b67d8(void *arg0) {
    s32 temp_r0;
    s32 var_r4;
    s32 temp_r5;
    void *temp_r0_2;
    void *temp_r6;

    if (M2C_FIELD(arg0, s32 *, 0x24) != 0) {
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
        func_020a1e54(1);
    }
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 8);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 8);
        func_02012da4(&data_02114e20, temp_r0);
    }
    func_020a0c0c();
    var_r4 = 1;
    temp_r0_2 = func_ov017_0218b5b0();
    temp_r5 = M2C_FIELD(temp_r0_2, s32 *, 0x36FC);
    temp_r6 = M2C_FIELD(temp_r0_2, void **, 0x3734);
    if (func_02046b60(temp_r5, 0x18) != 0) {
        var_r4 = 0;
    }
    if ((func_02046b60(temp_r5, 4) != 0) && (M2C_FIELD(temp_r6, u8 *, 0xCC) == 1)) {
        var_r4 = 0;
    }
    if (var_r4 == 0) {
        return;
    }
    M2C_FIELD(func_0202ae18(), s8 *, 0x1011) = 1;
}
