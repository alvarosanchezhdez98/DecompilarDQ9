#include <m2c.h>

M2C_UNK func_020489bc();
M2C_UNK func_020bc078(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_02052a4c(void *arg0) {
    func_020489bc();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x100);
    func_020bc078(arg0 + 0x198);
    M2C_FIELD(arg0, s32 *, 0x150) = 0;
    M2C_FIELD(arg0, s32 *, 0x154) = 0;
    M2C_FIELD(arg0, s32 *, 0x158) = 0;
    memset(arg0 + 0x178, 0, 4);
    M2C_FIELD(arg0, s8 *, 0x17C) = 0;
    M2C_FIELD(arg0, s8 *, 0x17D) = 0;
    M2C_FIELD(arg0, s32 *, 0x180) = -1;
    M2C_FIELD(arg0, s8 *, 0x17E) = 0;
    M2C_FIELD(arg0, s8 *, 0x17F) = 0;
    M2C_FIELD(arg0, s8 *, 0x184) = 0;
    M2C_FIELD(arg0, s32 *, 0x190) = 0;
    M2C_FIELD(arg0, s32 *, 0x194) = -1;
    M2C_FIELD(arg0, s8 *, 0x185) = 0;
    M2C_FIELD(arg0, s8 *, 0x186) = 0;
    M2C_FIELD(arg0, s32 *, 0x188) = 0;
    M2C_FIELD(arg0, s32 *, 0x1B4) = 0;
    M2C_FIELD(arg0, s32 *, 0x1B8) = 0;
    M2C_FIELD(arg0, s32 *, 0x1BC) = 0;
    M2C_FIELD(arg0, s32 *, 0x18C) = 0;
    M2C_FIELD(arg0, s32 *, 0x19C) = 0;
    M2C_FIELD(arg0, s16 *, 0x1B2) = 0;
    M2C_FIELD(arg0, s16 *, 0x1C0) = 0;
    M2C_FIELD(arg0, s32 *, 0x15C) = -1;
    M2C_FIELD(arg0, s32 *, 0x1C4) = 0;
}
