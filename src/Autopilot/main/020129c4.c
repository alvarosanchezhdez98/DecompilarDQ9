#include <m2c.h>

M2C_UNK func_020cddc0(s32);
s32 func_02012798(void *);

s32 func_020129b4(void *arg0) {
    s32 temp_r0;

    func_020cddc0(arg0 + 0x20);
    if (M2C_FIELD(arg0, u8 *, 0x5F) == 0) {
        if (M2C_FIELD(arg0, u16 *, 0x24) != 0) {
            return 0;
        }
        M2C_FIELD(arg0, u8 *, 0x5F) = 1U;
        goto block_4;
    }
block_4:
    if ((M2C_FIELD(arg0, u16 *, 0x24) != 0) && (M2C_FIELD(arg0, u16 *, 0x26) == 0)) {
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + 1);
        M2C_FIELD(arg0, s32 *, 0x48) = 0;
        if ((M2C_FIELD(arg0, u8 *, 0x56) != 0) && (func_02012798(arg0) > 1)) {
            M2C_FIELD(arg0, s32 *, 0x4C) = 0;
        } else if (func_02012798(arg0) < 1) {
            M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) + 1);
        }
    } else {
        M2C_FIELD(arg0, u16 *, 0x24) = 0U;
        temp_r0 = M2C_FIELD(arg0, s32 *, 0x40);
        if (temp_r0 != 0) {
            M2C_FIELD(arg0, s32 *, 0x44) = temp_r0;
        }
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + 1);
    }
    return 1;
}
