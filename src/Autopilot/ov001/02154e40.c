#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
s32 _ZNK9GameState12GetTickCountEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_0208bb78(void *, s32);
M2C_UNK func_0208beb4();
s32 func_02094a00();
M2C_UNK func_02094ab0(s32);
M2C_UNK func_02094b2c(s32, M2C_UNK, void *, M2C_UNK, s32);
M2C_UNK func_02094b40(s32);
extern M2C_UNK data_02114e20;

u16 func_ov001_02154e40(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 var_r6;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    if (!(M2C_FIELD(arg0, u16 *, 0x50) & 8)) {
        if ((M2C_FIELD(arg0, s32 *, 0x138) != 0) && (M2C_FIELD(arg0, void **, 0x120) != NULL)) {
            func_0208beb4();
            func_0208bb78(M2C_FIELD(arg0, void **, 0x120), _ZNK9GameState12GetTickCountEv(temp_r5));
            if ((s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x120), s16 *, 0xD2) >= 0) {
                return M2C_FIELD(arg0, u16 *, 0xA);
            }
            temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(M2C_FIELD(arg0, s32 *, 0x138));
            if (temp_r0 != 0) {
                _ZN13SafeAllocator7DestroyEv(M2C_FIELD(arg0, s32 *, 0x138));
                func_02012da4(&data_02114e20, temp_r0);
                M2C_FIELD(arg0, s32 *, 0x138) = 0;
            }
            M2C_FIELD(arg0, void **, 0x120) = NULL;
            goto block_10;
        }
        goto block_10;
    }
block_10:
    temp_r5_2 = func_02094a00();
    var_r6 = 1;
    temp_r0_2 = temp_r5_2;
    if (M2C_FIELD(arg0, u8 *, 0x13) != 0) {
        var_r6 = 0;
    }
    func_02094b40(temp_r0_2);
    func_02094ab0(temp_r5_2);
    func_02094b2c(temp_r5_2, 0x6F, arg0 + 0x62, 1, var_r6);
    return 0xDU;
}
