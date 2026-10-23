#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);

void func_ov004_0216aed0(void *arg0, s32 arg1, s16 arg2, s32 arg3) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    if (temp_r0 == NULL) {
        return;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) == 8) {
        M2C_FIELD(temp_r0, s16 *, 0x38) = arg2;
        if (arg3 == 1) {
            M2C_FIELD(temp_r0, u8 *, 0x45) = (u8) ((M2C_FIELD(temp_r0, u8 *, 0x45) & ~0x7E) | 4);
            M2C_FIELD(temp_r0, s16 *, 0x42) = 0;
        }
    }
}
