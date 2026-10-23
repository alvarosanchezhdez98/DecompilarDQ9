#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);

void func_ov004_021537a8(void *arg0, s32 arg1, M2C_UNK arg2) {
    void **temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(*temp_r0, M2C_UNK (**)(void **, M2C_UNK), 0x3C)(temp_r0, arg2);
}
