#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020a1e54(M2C_UNK);
M2C_UNK func_020a1f4c(M2C_UNK);
M2C_UNK func_ov017_021c12b0(M2C_UNK);
extern M2C_UNK data_02114e20;
extern s32 data_ov017_021d8478;

void func_ov017_021c1394(void *arg0) {
    s32 temp_r4;

    if (M2C_FIELD(arg0, u8 *, 0x1E) != 0) {
        func_ov017_021c12b0(0);
    }
    if (data_ov017_021d8478 != 0) {
        data_ov017_021d8478 = 0;
        func_020a1f4c(1);
        func_020a1e54(1);
    }
    temp_r4 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 8);
    _ZN13SafeAllocator7DestroyEv(arg0 + 8);
    func_02012da4(&data_02114e20, temp_r4);
}
