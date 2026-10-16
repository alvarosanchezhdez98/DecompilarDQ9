#include <m2c.h>

s32 func_02053dc0(M2C_UNK);
s32 func_ov024_021f691c(void *, M2C_UNK, s32, s16);
M2C_UNK func_ov024_021f8628(void *, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_ov024_021f9660(void *);

void func_ov024_021f8144(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_r0;

    temp_r0 = func_02053dc0(arg2);
    if (temp_r0 == 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x170) = 0;
    M2C_FIELD(arg0, s32 *, 0x124) = 0x3DA3D70A;
    func_ov024_021f9660(arg0);
    if (func_ov024_021f691c(arg0 + 0x4C8, arg3, temp_r0, M2C_FIELD(arg0, s16 *, 4)) != 0) {
        return;
    }
    if (func_ov024_021f691c(arg0 + 0x408, arg3, temp_r0, M2C_FIELD(arg0, s16 *, 4)) != 0) {
        return;
    }
    func_ov024_021f8628(arg0, arg1, arg2, arg3);
}
