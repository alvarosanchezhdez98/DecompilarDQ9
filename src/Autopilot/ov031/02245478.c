#include <m2c.h>

s32 func_ov031_022119d0(s32 *, u32 *);
M2C_UNK func_ov031_02245528(void *, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, s32);

void func_ov031_02245478(void *arg0) {
    s32 sp4;
    u32 sp0;
    s32 temp_r5;

    temp_r5 = func_ov031_022119d0(&sp4, &sp0);
    memset(M2C_FIELD(arg0, s32 *, 0x37C), 0, M2C_FIELD(arg0, s32 *, 0x380));
    M2C_FIELD(arg0, s32 *, 0x394) = (s32) (0 - sp4);
    switch (sp0) {
    default:
        break;
    case 0:
        M2C_FIELD(arg0, s32 *, 0x394) = 0;
        break;
    case 1:
        M2C_FIELD(arg0, s32 *, 0x394) = 0;
        break;
    case 6:
        if ((u32) (temp_r5 - 0xE) <= 1U) {
            M2C_FIELD(arg0, s8 *, 0x398) = 1;
        }
        break;
    case 7:
        M2C_FIELD(arg0, s8 *, 0x398) = 2;
        break;
    }
    func_ov031_02245528(arg0, 0);
}
