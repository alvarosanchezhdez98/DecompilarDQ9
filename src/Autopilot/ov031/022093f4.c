#include <m2c.h>

M2C_UNK CPSi_rc4_crypt(s32);

s32 decrypt(s32 arg0, s32 arg1, s32 arg2) {
    CPSi_rc4_crypt(arg0 + 0x1E0);
    return arg2;
}
