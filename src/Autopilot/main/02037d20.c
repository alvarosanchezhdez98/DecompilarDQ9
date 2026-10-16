#include <m2c.h>

M2C_UNK func_02052a4c();
M2C_UNK func_02038508(void *);

void func_02037d10(void *arg0) {
    func_02052a4c();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x800);
    M2C_FIELD(arg0, s8 *, 0x1CB) = -1;
    M2C_FIELD(arg0, s8 *, 0x1CC) = 0;
    M2C_FIELD(arg0, s8 *, 0x1C8) = -1;
    M2C_FIELD(arg0, s8 *, 0x1C9) = 0;
    M2C_FIELD(arg0, s8 *, 0x1CA) = -1;
    M2C_FIELD(arg0, s8 *, 0x1CD) = 0;
    M2C_FIELD(arg0, s8 *, 0x1CE) = 0;
    M2C_FIELD(arg0, s8 *, 0x250) = 1;
    M2C_FIELD(arg0, s8 *, 0x251) = 0;
    M2C_FIELD(arg0, s8 *, 0x252) = 1;
    M2C_FIELD(arg0, s8 *, 0x253) = 1;
    M2C_FIELD(arg0, s8 *, 0x254) = 0;
    M2C_FIELD(arg0, s32 *, 0x264) = 0;
    M2C_FIELD(arg0, s32 *, 0x260) = -1;
    M2C_FIELD(arg0, s8 *, 0x255) = -1;
    M2C_FIELD(arg0, s16 *, 0x256) = 0;
    M2C_FIELD(arg0, s32 *, 0x268) = 0;
    func_02038508(arg0 + 0x26C);
}
