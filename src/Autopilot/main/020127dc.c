#include <m2c.h>

M2C_UNK func_02012780();

void func_020127cc(void *arg0) {
    func_02012780();
    if ((s32) M2C_FIELD(arg0, s32 *, 0x38) < (s32) M2C_FIELD(arg0, u16 *, 0x20)) {
        M2C_FIELD(arg0, s8 *, 0x53) = 1;
    }
    if ((s32) M2C_FIELD(arg0, s32 *, 0x38) > (s32) M2C_FIELD(arg0, u16 *, 0x20)) {
        M2C_FIELD(arg0, s8 *, 0x51) = 1;
    }
    if ((s32) M2C_FIELD(arg0, s32 *, 0x3C) < (s32) M2C_FIELD(arg0, u16 *, 0x22)) {
        M2C_FIELD(arg0, s8 *, 0x52) = 1;
    }
    if ((s32) M2C_FIELD(arg0, s32 *, 0x3C) > (s32) M2C_FIELD(arg0, u16 *, 0x22)) {
        M2C_FIELD(arg0, s8 *, 0x50) = 1;
    }
}
