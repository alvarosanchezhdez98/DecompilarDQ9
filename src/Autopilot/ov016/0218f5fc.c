#include <m2c.h>

M2C_UNK _Z12NitroVM_SeekP7NitroVMii(s32, s32, M2C_UNK);
s32 _Z17NitroVM_ReadAsyncP7NitroVMPvi(s32, M2C_UNK, s32);

s32 func_ov016_0218f5fc(void *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r1;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r8;

    temp_r3 = M2C_FIELD(arg0, s32 *, 8);
    temp_r1 = temp_r3 & ~0x1FF;
    temp_r4 = temp_r3 - temp_r1;
    var_r8 = arg2 + temp_r4;
    if (var_r8 & (-0x200U >> 0x17)) {
        var_r8 = (var_r8 & ~0x1FF) + 0x200;
    }
    _Z12NitroVM_SeekP7NitroVMii(M2C_FIELD(arg0, s32 *, 0xC), temp_r1, 0);
    if (_Z17NitroVM_ReadAsyncP7NitroVMPvi(M2C_FIELD(arg0, s32 *, 0xC), arg1, var_r8) == -1) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + arg2);
    M2C_FIELD(arg0, s8 *, 0x10) = 1;
    return temp_r4;
}
