#include <m2c.h>

M2C_UNK func_020489bc();
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_02048614(void *arg0) {
    func_020489bc();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x400);
    M2C_FIELD(arg0, s32 *, 0x148) = 0;
    M2C_FIELD(arg0, s32 *, 0x144) = 0;
    M2C_FIELD(arg0, s8 *, 0x17C) = 0;
    M2C_FIELD(arg0, s8 *, 0x17D) = 0;
    M2C_FIELD(arg0, s8 *, 0x17E) = 0;
    M2C_FIELD(arg0, s8 *, 0x17F) = 0;
    M2C_FIELD(arg0, s8 *, 0x180) = 0;
    M2C_FIELD(arg0, s8 *, 0x181) = 0;
    M2C_FIELD(arg0, s8 *, 0x182) = 0;
    M2C_FIELD(arg0, s8 *, 0x183) = 0;
    M2C_FIELD(arg0, s8 *, 0x184) = 0;
    memset(arg0 + 0x14C, 0, 0x30);
    M2C_FIELD(arg0, s16 *, 0x186) = 0;
    M2C_FIELD(arg0, s16 *, 0x188) = 0;
    M2C_FIELD(arg0, s16 *, 0x18A) = 0;
    M2C_FIELD(arg0, s8 *, 0x18C) = 0;
    M2C_FIELD(arg0, s8 *, 0x18D) = 0;
    M2C_FIELD(arg0, s16 *, 0x18E) = 0x1000;
}
