#include <m2c.h>

M2C_UNK _Z40NitroVM_Command_AcquireCardReadResourcest(u16);
M2C_UNK _Z40NitroVM_Command_ReleaseCardReadResourcest(u16);
extern void *data_ov031_02290d24;

s32 ov13_0223F8A0(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 9:
        _Z40NitroVM_Command_AcquireCardReadResourcest(M2C_FIELD(data_ov031_02290d24, u16 *, 0xE4));
        return 0;
    case 10:
        _Z40NitroVM_Command_ReleaseCardReadResourcest(M2C_FIELD(data_ov031_02290d24, u16 *, 0xE4));
        return 0;
    case 1:
        return 4;
    default:
        return 8;
    }
}
