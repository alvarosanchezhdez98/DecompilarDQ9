#include <m2c.h>

M2C_UNK func_0206ee60(void *);
M2C_UNK func_0206efc4(void *);
M2C_UNK func_0209af34(void *);
M2C_UNK func_0209bc84(void *);
M2C_UNK func_0209bffc(void *);
M2C_UNK func_020a8e88(void *);
M2C_UNK func_020280b0(void *);

void func_020289c4(void *arg0) {
    M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) & ~4);
    M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) & ~8);
    M2C_FIELD(arg0, s16 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) & 0xFFFF000F);
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 0xD) = (s8) (0xFFFF000F >> 0x10);
    func_020280b0(arg0 + 0x18);
    func_0209bffc(arg0 + 0x44);
    func_0209bc84(arg0 + 0x60);
    func_0209af34(arg0 + 0x124);
    func_0206efc4(arg0 + 0x2F8);
    func_0206ee60(arg0 + 0x304);
    func_020a8e88(arg0 + 0x30C);
}
