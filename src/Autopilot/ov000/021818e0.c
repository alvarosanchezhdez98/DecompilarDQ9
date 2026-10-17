#include <m2c.h>

s32 func_ov000_0215ffa0();
void *func_ov000_02160094(void *);
void *func_ov000_021600f8(void *);

s32 func_ov000_021818e0(s32 arg0, s32 arg1, void *arg2, s32 *arg3) {
    switch (arg0) {                                 /* irregular */
    case 0:
        if ((s32) M2C_FIELD(arg2, u8 *, 9) < (s32) (arg1 + 1)) {
            return 0;
        }
        *arg3 = (s32) M2C_FIELD(func_ov000_021600f8(arg2), s16 *, 0xE);
        return 1;
    case 1:
        if ((s32) M2C_FIELD(arg2, u8 *, 8) < (s32) (arg1 + 1)) {
            return 0;
        }
        *arg3 = (s32) M2C_FIELD(func_ov000_02160094(arg2), u16 *, 0x20);
        return 1;
    case 2:
        if ((s32) M2C_FIELD(arg2, u8 *, 9) < (s32) (arg1 + 1)) {
            return 0;
        }
        func_ov000_021600f8(arg2);
        *arg3 = func_ov000_0215ffa0();
        return 1;
    default:
        return 0;
    }
}
