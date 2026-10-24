#include <m2c.h>

M2C_UNK __clear(M2C_UNK *, M2C_UNK);
M2C_UNK func_0203c108(void *, M2C_UNK *);
M2C_UNK func_0203c198(void *);
M2C_UNK func_ov000_02170ffc(void *);
s32 func_ov000_021719f8(void *);
s32 func_ov000_02171a74(void *, M2C_UNK *);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov000_0217f518(void *arg0) {
    M2C_UNK sp0[32];

    memset(arg0 + 0x10, 0, 8);
    M2C_FIELD(arg0, s8 *, 0x10) = 0xD;
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = -1;
    M2C_FIELD(arg0, s8 *, 0x20) = -1;
    M2C_FIELD(arg0, s16 *, 0x1E) = -1;
    M2C_FIELD(arg0, s8 *, 0x22) = -1;
    M2C_FIELD(arg0, s8 *, 0x21) = -1;
    M2C_FIELD(arg0, s16 *, 0x2C) = -1;
    M2C_FIELD(arg0, s8 *, 0x2E) = -1;
    M2C_FIELD(arg0, s16 *, 0x26) = 0;
    func_0203c198(arg0 + 0x50);
    M2C_FIELD(arg0, s8 *, 0x43D) = -1;
    if (func_ov000_021719f8(arg0) != 0) {
        __clear(sp0, 0x80);
        if (func_ov000_02171a74(arg0, sp0) >= 0) {
            func_0203c108(arg0 + 0x50, sp0);
        }
        M2C_FIELD(arg0, s8 *, 0x10) = 0x64;
    }
    func_ov000_02170ffc(arg0);
}
