#include <m2c.h>

void *func_02012fe4();
s32 func_0202c1a4(s32);

void func_ov017_021d1c84(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_r0;

    if (func_0202c1a4(arg4) == 0) {
        return;
    }
    temp_r0 = func_02012fe4();
    M2C_FIELD(temp_r0, s16 *, 0x27B4) = (s16) M2C_FIELD(arg1, u8 *, 4);
    M2C_FIELD(temp_r0, s16 *, 0x27B6) = (s16) M2C_FIELD(arg1, u8 *, 5);
}
