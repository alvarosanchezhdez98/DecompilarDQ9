#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);

void *func_ov004_02168ad4(void *arg0, s32 arg1) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), arg1);
    if ((temp_r0 != NULL) && (_ZN15MenuObjectClass7GetTypeEv(temp_r0) == 0xB)) {
        return temp_r0;
    }
    return NULL;
}
