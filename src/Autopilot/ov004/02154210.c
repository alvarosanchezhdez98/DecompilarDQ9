#include <m2c.h>

void * _ZN10MenuScript10GetObjectsEv(void *);
void * _ZN14MenuObjectList4FindEi(void *, s32);
u16 _ZN15MenuObjectClass7GetTypeEv(void *);
void _ZN17MenuObjectClass107SetItemEs(void *, s16);

s32 func_ov004_02154210(void *arg0) {
    void *temp_r0;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(arg0), 0x2E);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv(temp_r0) != 0x10) {
        return 0;
    }
    _ZN17MenuObjectClass107SetItemEs(temp_r0, -1);
    return 0;
}
